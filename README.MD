# IRIS
------

Purpose of this project is to provide software implementation for vectorizing intrinsics available on ARM and x86 processors.

Additionally:
* Ability to target and test software that uses ARM NEON intrinsics on x86 machines
* Ability to target and test x86 intrinsics from newer architectures when corresponding hardware is not yet available ( April 2017 - Intel Cannonlake)

#### Intrinsics to be supported:
* ARM
    * NEON
    * SVE
* x86
    * MMX
    * SSE
    * SSE2
    * SSE3
    * SSE4.1
    * SSE4.2
    * AVX
    * AVX2
    * FMA
    * AVX-512
        * AVX-512F
        * AVX-512BW
        * AVX-512CD
        * AVX-512DQ
        * AVX-512ER
        * AVX-512IFMA52
        * AVX-512PF
        * AVX-512VBMI
        * AVX-512VL
    * KNC

Current implementation status is available here: [Status Summary](https://docs.google.com/spreadsheets/d/1H0BMm1WNZbmqU08OF6IEh1O1Io6G4MI7xHDM-IHPwb8/edit#gid=1193430138)
