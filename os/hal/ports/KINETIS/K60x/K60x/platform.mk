# List of all platform files.
PLATFORMSRC = ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/hal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/pal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/serial_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/spi_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/i2c_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/ext_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/adc_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/gpt_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/st_lld.c

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/ports/common/ARMCMx \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60x/ \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD
