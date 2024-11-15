# Remarks on introduction lab

The first lab introduced you to the environment and some debugging tools. 

Some key concepts from this lab:
- Figuring out that one tick was one millisecond. This is how FreeRTOS was setup in this case.
- Realizing that the button was a normally closed button, meaning that pushing the botton caused the pin to be disabled or reset and not pushing the button caused the pin to be active.
- Checking rising or falling edge on the button rather than just it's state. Since the thread was running every millisecond a press on the button could cause the led to turn on and off several times causing an irratic behavior, if not handled properly.