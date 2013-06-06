#include "Callback/Receptor.h"
#include "Callback/Emitter.h"

using namespace Callback;

Receptor::Receptor(Functor callback)
   : m_CallbackFunctor(callback)
{}

Receptor::~Receptor()
{
   Detach();
}

void Receptor::AttachTo(Emitter& emitter)
{
   // Detach from the previous connection.
   Detach();

   m_DetachFunctor = emitter.Attach(*this, m_CallbackFunctor);
}

void Receptor::Detach()
{
   if(m_DetachFunctor)
   {
      m_DetachFunctor();
      m_DetachFunctor = nullptr;
   }
}
