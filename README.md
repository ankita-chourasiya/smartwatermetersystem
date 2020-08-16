# smartwatermetersystem
Smart water meter system is concern for proper utilization of water. As we all know that water consumption and wastage increase day by day. Some irresponsible people are overusing the water and wasting it daily and due the these a large population not getting the pure drinking water. This problem is occure due to the irregular distribution of water. In this project, we are going to make a smart water meter system that measures our daily water usage and provide live data on web server .

In that project various components are used :

Water flow sensor : water flow sensor is used to measure the flow rate of water and calculate the amount of water flowed through the pipe.

NodeMCU ESP8266 : NodeMCU ESP8266 is a wifi module .These module is used in project to access the wifi or internet. It can communicate with any microcontroller and make the projects wireless.

Arduino UNO : The Arduino UNO is a microcontroller. It as a number of sockets that can be wired up to external electronics such as sensor, relay etc. Arduino control all the device that are connected to it. They can powered either through USBconnection from the computer or from a 9 volt battery.

Solenoid Valve : Solenoid valve is used to control the flow of water. Through relay solenoid valve control the flow when relay get ON the water get flow but when relay get OFF the water flow getting stop.

There are the various module: 
• Firstly we connect the WIFI through NodeMCU and then generate the flow rate of water through water flow sensor and that flow rate store in the database through WIFI. 
• After these we establish the connection of solenoid valve. In that various components are used that was Valve, relay for ON OFF the valve, 12Valt adapter, Arduino UNO, button. In these when we press the button the relay ON and the water will flow but when we release the button the relay OFF and the water flow getting stop.
• I also design the Inverter for access the WIFI when light was gone. To design the inverter various components are used that was transformer 9-0-9 , transistor TIP41, 1K ohm resister , 12valt battery.
