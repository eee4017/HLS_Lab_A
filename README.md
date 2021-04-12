# HLS_Lab_A FFT Transform


This repository is contructed as below. There are three versions of code:
+ `fixed` contains a Radix-2 FFT using ap_fixed

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
│       ├── fft_fixed.cpp
│       ├── fft_fixed.h
│       ├── fft_fixed_test.cpp
│       ├── utils.cpp
│       └── utils.h
└── README.md

5 directories, 13 files
```


