# List of all platform files.
PLATFORMSRC = ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/hal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/pal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/serial_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/spi_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/i2c_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/ext_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/adc_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/gpt_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/st_lld.c

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/ports/common/ARMCMx \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60Dx/ \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD
