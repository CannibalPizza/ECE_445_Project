# Love's Worklog

## 02/11/2025 - First Meeting with TA
This was our first meeting with out TA, Chi Zhang. We were discussing our project proposal and a few notes from the meeting included the following:
1. Highlevel requirements should be quantifiable
2. We needed to discuss with the professor about how we should demo our project
3. Better the block diagram such that each block has specific component names and the connects are properly labeled
4. Most of the proposal should mention measurable stuff much as the delay or response time of the systems

With this information, my group and I discussed these aspects and prepared the project proposal for the final submission. 

## 02/13/2025 - Talk with Machine Shop
After emailing the professor regarding our demonstration for the final demo, Romeo and I talked with the Machine Shop to see if they had a door that was scaled down for demonstration purposes. They provided us with a door that will fit well for our project demonstration. We also discussed aspects of which motor to use to help with the Door Opener System and we were suggested a 12V DC gear motor. With this information, my group and I updated our proposal to reflect our scaled down door and determined parts based on that. 

![Image](Door.png)

## 02/19/2025 - Proposal Review with Professor
We presented our final proposal in front of the Professor Gruev. In terms of complexity, the professor approved the project but the group was unaware of how we were doing to drive the 12V DC gear motor. Professor Gruev told us to focus on that aspect of the project to ensure we understand what is going on. He also suggested that instead of using a voltage regulator to step down certain voltages, we should look into LDO.

## 02/22/2025-02/24/2025 - Research on H-Bridge Motor Driver and LDO
After the propsoal review, I did some research on the H-bridge motor driver and LDO. Essentially what I learned was that we should be using mosfets, specifically nMOS to control our motor spinning in the forward or reverse direction. An LDO is needed when we are stepping down a voltage by very little so since we were using a regular voltage regualtor to go from 3.6V to 3.3V in the Remote Control Power Subsystem, we should consider using an LDO. With Alex, I determined that we can use AP2112K-3.3TRG1, which works perfectly for what we were trying to achieve in that power subsystem. 

## 02/25/2025 - Meet-up with Groupmates
I met up with Romeo and we discussed how the ESP32 will connect with the H-bridge motor driver. We believe that the GPIO pins from the ESP32 should be going to the gates of the mosfets to determine if the motor will spin forward or in the reverse direction. We also looked into how the Bluetooth function of the ESP32 works. Essentially for this, the remote will act as the server while the Door Opener System should be the client which will allow the two to communicate. For the Latch System, we are still thinking if we want the remote to send a signal to it for whether the remote should send a signal to the Door Opener System which then sends a signal to the Latch System. We feel the second way will be easier but the first method might allow for a faster response time. So with that we are still considering what to do. Below is a basic drawing of what our H-bridge will look like:

![Image](H-Bridge_Motor_Driver_Basic.png)

We also had our weekly TA meeting where we shared the progress of our project. We wanted to discuss how the BlueTooth singals where going to work in our project because we believe that it will be suitble to go from the remote to door to latch back to door and then remote. We also breiefly discussed about getting parts and stuff for the project.

## 02/26/2025 - Remote PCB Design
I met up with Romeo to work on the PCB design for our remote control. We discussed about the layout of our PCB designs and determined that we will need three different PCB designs since each of our main subsystems have their own power system and it will be easier to communicate that way between the subsystem. We started by determining what parts will be needed for the remote PCB and started putting down the design on KiCad. We followed our block diagram in order to create the design and answered any questions that popped up as we went along designing the PCB. We are unsure of how the 7-segment display is going to connect but added a connector for it at the moment to have it ready for the PCB design review.

## 02/27/2025 - Door Latch PCB Design
I met up with Romeo again to work on our next susbsystem PCB design which is the Door Latch. We were trying to get this one done as well so that Romeo and Alex can attend the PCB review and get feedback on them. The designing did not take long as we followed the block diagram again and this seemed like the simple one out of all the other ones. We needed to figure out how to determine if the lacth was retracted or not so we decided to use an NMOS gate to control that and needed to find one that can take 3.3V for the gate input with a 12V difference between the drain and source. We also added another signal from the latch to the ESP32 so used a voltage regulator to step down the 12V signal to a 3.3V signal. Besides these changes everything else was the same. 

![Image](Latch_Schematic.png)

![Image](Latch_PCB.png)

## 03/04/2025 - Weekly TA Meeting
Today we had an exam for a class so we were only able to attend the TA meeting and not work further on the project. During the PCB review, the TA that met with the group mentioned we needed an UART connection in order the program the PCBs so that was the topic of discussion with the TA. We did not discuss much because we did not have any progress on the project or the PCB designs. The TA informed that there may be the USB to UART bridge that we can use to program our ESP32s but wasn;t sure if the lab had anymore left so we talked about that. We discussed alittle bit more about getting parts as well. 

## 03/05/2025-03/06/2025 - Working on Design Document
In these two days, the group worked on the design document by expanding on the proposal. We also had our parts determined by the end of the second day since that needed to be included within our Design Document. We mainly discussed about the project and started finalizing the entirety of it as we worked on the document. We updated our block diagram to ensure it reflected the different changes we had in the project such as the inclusion of the H-Bridge and how the BlueTooth signals were going to work. We also complete the PCB design for our Door Opener subystem as that was the last one we had left after the PCB review. We also determined a temporary schedule for the next few weeks leading up to the final demo in order to stay on track with the project. We faced a few challenges such as whether or not our connections were right and which parts we needed exactly but we worked through it and researched regarding it to reach a final conlusion. 

## 03/07/2025 - Office Hour Meeting to Determine How to Program for the Breadboard Demo
We were having difficulty understand how we will use the ESP32 chips for the breadboard demo so Romeo and I went to office hours to determine this. The TA during that time told us that we should use the ESP32 Dev Kits for the breadboard demo and also with any programming we will due for the project since it will make our job easier for now. So we went to the supply center to purchase those and luckily we got the last two that were there. We needed two since we will need two to communicate as one will send the signal and the other will receive it and relay it to the motor driver to get the motor spinning. 

## 03/10/2025-03/11/2025 - Working on Breadboard/Breadboard Demo
These two days, we needed to work on the breadboard demo since we were busy leading up to it. The first day I worked on trying to set up the H-bridge Motor Driver since were were going to demo the motor running through BlueTooth signals. So the other teammates worked on determining how to program the ESP32 Dev Kit so that it can be used to send signals to the motor for it to start spinning in either the reverse or forward direction. With the motor driver, I was having isssues regarding floating voltages around the circuit and also had forgotten to debounce the circuit. We also didn't have batteries that were properly powering the circuit or the ESP32 Dev Kit so we had to go into lab to use the pwoer supplies there. Once we reached the lab, we figured out we needed a pull-down resistor to combat the floating voltage for the motor driver. we used a 1 M-ohm resistor and the h-bridge motor driver was finally working. Now we needed the ESP32 to be programmed so that it can connect to the motor driver. The biggest issue with this was that the datasheet given to us for the Dev Kit was wrong so we needed to determine which pins where which. This took up most of our time that day but still were were unsucessfull in getting the ESP32 to send signals to the motor driver. We were able to recieve signal from one ESP32 to our phone and also send a signal to our phone but were not able to connect the two ESP32s to send and receive signals between them. In the end, we gave up and decided we will try one last time before the demo the second day. We were still unsucessful the next day so we decided to demo the two things separetely. We had the motor driver spinning the motor in two directions using buttons and used out phones to show the ESP32s being able to send and receive signals. The demo went well as the professor said that this was sufficient and now we just needed to focus on getting the PCB designs done and submitting them for the order. 

## 03/12/2025 - Finalize PCB Designs
We needed out PCB designs to be finalized today since we needed to submit the order for it the following day. We finished the schematics and had to change our ESP32 schematic since we were using the wrong one. We had the right one first but then since we were using the ESP32 Dev Kit for the breaboard demo we thought we need to use that datasheet for our PCB so we tried to find that one and change our connections for that. But then we faced the issue of not having the footprint for it so we had to switch back to the orignal one which ended up being the right one. This wasted our time with the schematic but after that we finally moved on to transferring the schematic to the PCB. We designed the PCBs and then went on to submitting it to pass the machine audit on PCBway. Mine passed but my groupmates had to revise so we ended up finishing it the following day and getting it submitted. 

## 03/14/2025 - Talk with Machine Shop
Romeo and I went to give the machine shop our PCB dimensions and our parts such as the motor and the latch that we had ordered for the project. They needed it to start mounting it on the door. We also needed them to order the housing for the PCBs thus the PCB dimensions but they told us to come back with the PCBs when they come in since it will be easier to order the hosuing boxes when they physically have it.

## 03/31/2025 - Redesigning the Door PCB
For the third order PCB, we decided to change the Door subsystem PCB. For the power supply we were using a connector on the PCB but we decided to change it to a power adapter so that we can plug the power supply straight into it. I looked up the footprint for the adapter and re-did the connections on the PCB. There was no other change as everything else seemed to be fine at the moment. We continued with testing the PCBs to see if they were receiving the proper voltages and stuff. 

![Image](Door_Connector_Schematic.png)

![Image](Door_Connector_PCB.png)

## 04/03/2025-04/17/2025 - Continuing work and testing on PCBs
In these two weeks, the group continued to work on the testing of the PCBs. We ran into problems with programming and also physical connections on the PCB. The boards were not being programmed since there used to be some problem with the connections to the UART bridge. We tried to rewire our connections and were able to then program the remote control PCB but the latch and door were still giving issues. We talked with the TA and they said that our programming circuit seemed correct so they were not sure what the issue was either. For a few days we had issues with this until eventually we resoldered and tried programming them again, which then worked. I resoldered the latch PCB hoping the connections were just not done right. The remote control PCB was programmed but the test on it was not working. We realized that the ground was reading 3.3V for the ESP32 so we needed to resoldered that one as well. Once the remote and latch were resoldered, we fixed the connections with the UART bridge and were able to program the two PCBs. Both were then tested with their respective tests and they seemed to work fine. The door PCB was giving problems with programming so we are going to resoldered that since it seemed like there may have been some physical connections issue on it. We also placed an order for our latch and remote PCB for the fourth round. The remote just needed to be redesigned so that we can see the values of each part on the PCB to make it easier to solder parts onto it. For the latch, when I had designed it the first time, I made the mistake of having vias on the pads for GPIO strapping of pins GPIO46 and GPIO3, so I had changed that hoping that would solve our issue in terms of why we were not able to program it. But before the fourth order PCBs come in, we were able to program the latch and remote. In the middle of this time frame we had to stop working since we did not have parts to solder so the group decided to place mass order of parts so that we did not have to wait and waste our time until the parts came.

## 04/15/2025 - Talk with Machine Shop for PCB boxes
Romeo and I went to the machine shop with our PCBs so that they can order boxes to house our PCBs. We gave them the full details and also told them how many holes we want for each box. The next day I followed up with them since they wanted to see where we wanted the holes on the boxes. I guided them in pointing out how big and where the holes should be. We also told them to make an extra box for the door PCB since we will be demoing with two door systems just by showing that the single remote can operate on both.

## 04/22/2025 - Mock Demo
We were not able to get out project fully working for the mock demo but we demonstrated the remote control being able to run a simple program and the latch retracting every 5 seconds. The second did not work cause then it started having issues with the PCB heating up but we were able to figure that it had a bad solder joint to the PCB so we fixed that. 

## 04/28/2025-04/30/2025 - Finalizing Product/Final Demo
These few days, we worked on getting the project to work. We still need out door PCB to be soldered properly since it was having issues with the voltage regulator heating up reaally quickly once connected to power. During this process we burnout a motor and a door PCB, but thankfully we had more parts to solder another door PCB and get it working. Our Latch and Remote Control were operational and could run simply tests on it. On the 29th, Romeo was able to figure out the Bluetooth connections between the devices so we were able to finally connect all of our parts. He did face a few issues but was able to figure it out at the end.  Romeo finished up the code while I boxed everything up to make it look clean for our final demo.

Door Box:

![Image](Door.png)

Motor Box:

![Image](Motor.png)

Latch Box:

![Image](Latch.png)

Remote Box:

![Image](Remote.png)
