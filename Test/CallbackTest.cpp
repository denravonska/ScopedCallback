#include "Callback/Receptor.h"
#include "Callback/Emitter.h"

#include "catch.hpp"

namespace
{
   void IncreaseAndStore(int& counter, int& storage)
   {
      storage = ++counter;
   }

   template<typename T>
   void Assign(T& ref, T& value)
   {
      ref = value;
   }
}

TEST_CASE("Scope",
          "Tests which only demonstrates the deregistration when the components goes out of scope")
{
   SECTION("ReceptorDestructor", "detach from Emitter.")
   {
      Callback::Emitter emitter;
      bool called(false);

      {
         Callback::Receptor receptor(std::bind(Assign<bool>, std::ref(called), true));
         receptor.AttachTo(emitter);
         // After this the receptor should detach from the emitter.
      }

      // This should be safe and the callback should not be called.
      emitter();
      REQUIRE_FALSE(called);
   }

   SECTION("EmitterDestructor", "detach Receptor")
   {
      // This test only verifies that nothing crashes.
      Callback::Receptor receptor;

      {
         Callback::Emitter emitter;
         receptor.AttachTo(emitter);
         // Emitter goes out of scope which till tell the receptor to detach.
      }
   }
}

TEST_CASE("Emitter",
          "Tests for the Emitter class")
{
   SECTION("TriggerShouldCallCallback",
           "Verifies that Emitter::Trigger triggers the specified callback.")
   {
      bool called(false);
      Callback::Receptor receptor(std::bind(Assign<bool>, std::ref(called), true));
      Callback::Emitter emitter;

      receptor.AttachTo(emitter);
      emitter();
      REQUIRE(called);
   }

   SECTION("DoubleAttach",
           "Verifies that existing receptors are detached if a new one is attached.")
   {
      int counter = 0;
      int firstCounter = 0;
      int secondCounter = 0;
      Callback::Receptor first(std::bind(IncreaseAndStore, std::ref(counter), std::ref(firstCounter)));
      Callback::Receptor second(std::bind(IncreaseAndStore, std::ref(counter), std::ref(secondCounter)));
      Callback::Emitter emitter;

      // Attach the receptors to the emitter and trigger callbacks.
      first.AttachTo(emitter);
      emitter();
      second.AttachTo(emitter);
      emitter();
      REQUIRE(firstCounter == 1);
      REQUIRE(secondCounter == 2);
   }
}

TEST_CASE("Receptor",
          "Tests for the Receptor class")
{
   SECTION("Detach",
           "Verifies that Detach detaches the receptor from the emitter")
   {
      bool called(false);
      Callback::Receptor receptor(std::bind(Assign<bool>, std::ref(called), true));
      Callback::Emitter emitter;

      receptor.AttachTo(emitter);
      receptor.Detach();
      emitter();
      REQUIRE_FALSE(called);
   }
}
