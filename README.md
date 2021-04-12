# HLS_Lab_A FFT Transform


This repository is contructed as below. There are two versions of code:
+ `fixed` contains a Radix-2 FFT using ap_fixed
+ `float` contains a Radix-2 FFT using IEEE 754 double

```
.
├── fixed
│   ├── dat
│   │   ├── cos_qtable.txt
│   │   ├── gen.py
│   │   └── sin_qtable.txt
│   ├── rpt
│   │   ├── fft_fixed_cosim.rpt
│   │   └── fft_fixed_csynth.rpt
│   ├── script
│   │   ├── directives.tcl
│   │   └── script.tcl
│   └── src
│       ├── ac_complex.h
│       ├── ac_fixed.h
│       ├── ac_float.h
│       ├── ac_int.h
│       ├── fft_fixed.cpp
│       ├── fft_fixed.h
│       ├── fft_fixed_test.cpp
│       ├── utils.cpp
│       └── utils.h
├── float
│   ├── dat
│   │   ├── cos_qtable.txt
│   │   ├── gen.py
│   │   └── sin_qtable.txt
│   ├── rpt
│   │   ├── fft_fixed_cosim.rpt
│   │   └── fft_fixed_csynth.rpt
│   ├── script
│   │   ├── directives.tcl
│   │   ├── export.tcl
│   │   └── script.tcl
│   └── src
│       ├── ac_complex.h
│       ├── ac_fixed.h
│       ├── ac_float.h
│       ├── ac_int.h
│       ├── fft_fixed.cpp
│       ├── fft_fixed.h
│       ├── fft_fixed_test.cpp
│       ├── utils.cpp
│       └── utils.h
└── README.md
```


