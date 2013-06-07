#include "Callback/Emitter.h"
#include "Callback/Receptor.h"

using namespace Callback;

Emitter::~Emitter()
{
   DetachReceptor();
}

Functor Emitter::Attach(Receptor& receptor, Functor callback)
{
   // Remove the previous receptor attachment if one is attached.
   DetachReceptor();

   m_CallbackFunctor = callback;

   // Setup the detachment functor this emitter will use when it goes out of scope. The functor will call Detach on
   // the receptor which will cause it to execute and clear its own detachment functor. This setup will prevent memory
   // corruption if the Emitter goes out of scope before the Receptor.
   m_DetachFunctor = std::bind(&Receptor::Detach, &receptor);

   // Return a detachment functor the connector can use when it goes out of scope, or if the user attaches the
   // receptor to a different callback.
   return std::bind(&Emitter::OnReceptorDetached, this);
}

void Emitter::operator()() const
{
   if(m_CallbackFunctor)
      m_CallbackFunctor();
}

void Emitter::DetachReceptor()
{
   if(m_DetachFunctor)
      m_DetachFunctor();
}

void Emitter::OnReceptorDetached()
{
   m_CallbackFunctor = nullptr;
   m_DetachFunctor = nullptr;
}
