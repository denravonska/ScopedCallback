#pragma once

#include "Callback/Fwd.h"

namespace Callback
{
   //! \author Marco Nilsson <denravonska@gmail.com>
   //! \brief Callback receptor.
   //!
   class Receptor
   {
   public:
      //! \brief Constructor.
      //!
      //! \param callback Callback functor to attach to receptor. This is the functor which will be called when
      //! \ref Emitter::Trigger "Trigger()" is called on the attached emitter.
      Receptor(Functor callback);

      //! \brief Default constructor.
      Receptor() = default;

      //! \brief Destructor.
      //!
      //! This detaches the receptor from its emitter.
      ~Receptor();

      //! \brief Attach receptor to emitter.
      //!
      //! Detaches the receptor from its current emitter attachment and attaches itself to \p emitter instead.
      void AttachTo(Emitter& emitter);

      //! \brief Detach from emitter.
      //!
      //! Detaches the receptor from its emitter attachement. Since this uses the functor given to the receptor in
      //! AttachTo, this will notify the emitter that the receptor has been detached.
      void Detach();

   private:
      Functor m_CallbackFunctor;
      Functor m_DetachFunctor;
   };
}
