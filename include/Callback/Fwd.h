#pragma once

#include <functional>

namespace Callback
{
   class Emitter;
   class Receptor;

   //! \brief Standard, parameterless functor.
   typedef std::function<void()> Functor;
}
