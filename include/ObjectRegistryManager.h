#ifndef OBJECTREGISTRY_H
#define OBJECTREGISTRY_H

#include <vector>
#include <sstream>

template<class TBase>
class ObjectRegistryManager
{
public:
    /*
    template<class TFactory>
    TFactory* ObjectFactory()
    {
        return new TFactory;
    }
    */

    class ObjectRegistry
    {
    public:
        typedef typename std::vector<TBase*>::iterator iterator;
        static ObjectRegistry& get()
        {
            static ObjectRegistry instance;
            return instance;
        }
        template<class TAdd>
        void add(TAdd* creator)
        {
            mv_Objects.push_back(creator);
        }
        iterator begin()
        {
            return mv_Objects.begin();
        }
        iterator end()
        {
            return mv_Objects.end();
        }
    private:
        std::vector<TBase*> mv_Objects;
    };
    
    class ObjectRegistration
    {
    public:
        template<class TRegistration>
        ObjectRegistration(TRegistration* creator)
        {
            ObjectRegistry::get().add(creator);
        }
    };
    
    
    static typename std::stringstream getRegisteredNames()
    {
        std::stringstream registeredNames;
        // lamda to get rid of static errors with calling the getName function
        auto getName = [] (TBase* component) {return component->getName();};
        ObjectRegistry& registry(ObjectRegistry::get());
        for( typename ObjectRegistry::iterator it = registry.begin(); it != registry.end(); ++it)
        {
            TBase* comp = *it;
            registeredNames << getName(comp) << " ";
        }
        return registeredNames;
    }
    
    template<class TReg>
    static void RegisterObject()
    {
        ObjectRegistration(new TReg);
    }
};
#endif
