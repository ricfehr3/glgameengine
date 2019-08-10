#ifndef OBJECTREGISTRY_H
#define OBJECTREGISTRY_H

#include <vector>

template<class TBase>
class ObjectRegistryManager
{
public:
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
};
#endif
