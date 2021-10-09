HAPRAD_CPP/Utilities
====================

**(Branch: aborquez/analysis-omega)**

`GetRC` uses the dynamic library `TRadCor` to do radiative corrections calculations.

## Environment

Feel free to modify the variables in `set_env.sh` according to your own environment.

## Usage

**Important:** `GetRC` should only work after the correct execution of all macros in `analysis-omega/macros/rad-corr_<particle>` from the [**analysis-omega**](http://github.com/utfsm-eg2-data-analysis/analysis-omega) repository.

1. Do `source set_env.sh`.

2. Execute `./exec_rad-corr_chain.sh --part <part>` where `<part> = (eta, omega)`.

## Compilation

Do `source set_env.sh` and compile the programs by running `make`.
