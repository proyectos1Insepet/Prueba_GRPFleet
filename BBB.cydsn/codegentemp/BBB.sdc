# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Recepcion\Desktop\Prueba_GRPFleet\BBB.cydsn\BBB.cyprj
# Date: Wed, 27 Apr 2016 12:43:29 GMT
#set_units -time ns
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 16.666666666666664 -waveform {0 8.33333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 16.666666666666664 -waveform {0 8.33333333333333} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {LCD_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 131 261} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {LCD_2_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 131 261} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {PC_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 781 1563} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 1305 2609} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {timer_clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 60001 120001} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_clock -name {timer_clock_1(fixed-function)} -period 1000000 -waveform {0 16.6666666666667} [get_pins {ClockBlock/dclk_glb_ff_4}]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\Recepcion\Desktop\Prueba_GRPFleet\BBB.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Recepcion\Desktop\Prueba_GRPFleet\BBB.cydsn\BBB.cyprj
# Date: Wed, 27 Apr 2016 12:43:16 GMT