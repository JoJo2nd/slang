@echo off

set FXC="C:\Program Files (x86)\Windows Kits\8.1\bin\x64\fxc.exe"

REM %FXC% /?

%FXC% first.hlsl /T vs_4_0_level_9_3 /E main_vs /Fc first.hlsl.vs.fco /nologo
%FXC% first.hlsl /T ps_4_0_level_9_3 /E main_ps /Fc first.hlsl.ps.fco /nologo
%FXC% var_types.hlsl /T vs_4_0_level_9_3 /E main_vs /Fc var_types.hlsl.vs.fco /nologo
%FXC% var_types.hlsl /T ps_4_0_level_9_3 /E main_ps /Fc var_types.hlsl.ps.fco /nologo
%FXC% var_types.hlsl /T vs_4_0 /E main_vs /Fc var_types.hlsl.vs_4_0.fco /nologo
%FXC% var_types.hlsl /T ps_4_0 /E main_ps /Fc var_types.hlsl.ps_4_0.fco /nologo
%FXC% var_types.hlsl /T vs_5_0 /E main_vs /Fc var_types.hlsl.vs_5_0.fco /nologo
%FXC% var_types.hlsl /T ps_5_0 /E main_ps /Fc var_types.hlsl.ps_5_0.fco /nologo
