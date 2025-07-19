workspace "Demo-Bird-Simulator"
    architecture "x64"
    configurations { "Debug", "Release" }    
    startproject "Demo-Bird-Simulator"

    flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"