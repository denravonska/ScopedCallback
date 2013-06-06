#pragma once

#include "Callback/Fwd.h"

namespace Callback
{
   //! \author Marco Nilsson <denravonska@gmail.com>
   //! \brief Callback emitter.
   //!
   //! Emitter used to trigger callbacks defined by the client code.
   class Emitter
   {
      // Friend declaration of Receptor to enable it to call Attach without exposing the method.
      friend class Receptor;

   public:
      //! \brief Destructor.
      //!
      //! This will tell the attached receptor to detach.
      ~Emitter();

      //! \brief Trigger callback.
      //!
      //! Triggers the callback from Attach() if it exists. This will call the callback passed to the
      //! \ref Receptor::Receptor(Functor) "receptor constructor".
      void Trigger() const;

   private:
      //! \brief Attach receptor to emitter.
      //!
      //! Attaches the receptor and callback to this emitter.
      //!
      //! \param receptor Receptor to attach to emitter.
      //! \param callback Callback to call in Trigger().
      //!
      //! \returns detachment functor to call when the receptor goes out of scope or attaches to another emitter.
      //! If this functor is not saved and used in Receptor::Detach or else the automatic detachment will not work.
      Functor Attach(Receptor& receptor, Functor callback);

      //! \brief Detach receptor from emitter.
      //!
      //! If attached, this will tell the attached receptor to detach from this emitter.
      void DetachReceptor();

      //! \brief
      void OnReceptorDetached();

      Functor m_CallbackFunctor;
      Functor m_DetachFunctor;
   };
}
