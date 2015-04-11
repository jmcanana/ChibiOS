# List of all platform files.
PLATFORMSRC = ${CHIBIOS}/os/hal/ports/common/ARMCMx/nvic.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/hal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/pal_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/serial_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/spi_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/i2c_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/ext_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD/adc_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/gpt_lld.c \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/st_lld.c

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/ports/common/ARMCMx \
              ${CHIBIOS}/os/hal/ports/KINETIS/K60x/K60F120/ \
              ${CHIBIOS}/os/hal/ports/KINETIS/LLD
