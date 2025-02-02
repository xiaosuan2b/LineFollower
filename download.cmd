openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/Debug/car_green.hex verify reset exit"
    