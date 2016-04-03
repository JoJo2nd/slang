# slang
The goal of slang is to be a write once, deploy anywhere GPU shader language. 

Basically, I got fed up writting things twice (in HLSL & GLSL) or hacking things up with macros and with SPIR-V and DXIL coming slang seemed like a good idea.

It's very early days, the plan is to get slang->HLSL working first with slang->GLSL working quickly after. Then probably slang->LLVM->(SPIR-V or DXIL) but GLSL->SPIR-V & HLSL->DXIL may work well enough.
