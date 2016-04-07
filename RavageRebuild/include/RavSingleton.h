#ifndef RAVSINGLETON_H_INCLUDED
#define RAVSINGLETON_H_INCLUDED

/* PART OF RAVAGE BASE */

namespace Ravage
{
    template <class Type>
    class Singleton
    {
        public:
            static Type* instance()
            {
                if (mCounter++ > 0)
                    return mObject;
                return mObject = new Type;
            }

            static void freeInst()
            {
                if (--mCounter <= 0)
                    delete mObject;
            }
        protected:
            Singleton() {}
            virtual ~Singleton() {}
        private:
            static int mCounter;
            static Type* mObject;
    };

    template <class Type>
    int Singleton<Type>::mCounter = 0;

    template <class Type>
    Type* Singleton<Type>::mObject = 0;
}

#endif // RAVSINGLETON_H_INCLUDED
