# PX4

* PX4 is the _Professional Autopilot_. PX4 is powerful open source autopilot _flight stack_.

*   * Unmanned Aerial Vehicles (UAV), 
    * Unmanned Aerial Systems (UAS), 
    * Unmanned Ground Vehicles (UGV), 
    * Unmanned Surface Vehicles (USV), 
    * Unmanned Underwater Vehicles (UUV).

* PX4 is a core part of a broader drone platform that includes the **QGroundControl** ground station, **Pixhawk hardware**, and **MAVSDK** for integration with companion computers, cameras and other hardware using the _MAVLink_ protocol.

* PX4 was initially designed to run on **Pixhawk Series** controllers, but can now run on Linux computers and other hardware.

* The Pixhawk connector standard is intended for in-vehicle, cross-PCB use. It uses the JST GH series, which offers a latch lock mechanism at a small size and a very competitive cost, and it's used across multiple Pixhawk Standards as the default connector.

* Typically the `MAIN OUT` port is used for core flight controls while `AUX OUT` is used for non-critical actuators/payloads (though AUX may be used for flight controls if there aren't enough MAIN ports for the vehicle type- e.g. VTOL).

* Many PX4 drones use brushless motors that are driven by the flight controller via an Electronic Speed Controller (ESC) (the ESC converts a signal from the flight controller to an appropriate level of power delivered to the motor).

* PX4 drones are mostly commonly powered from Lithium-Polymer (LiPo) batteries. The battery is typically connected to the system using a Power Module or Power Management Board, which provide separate power for the flight controller and to the ESCs (for the motors)

* PX4 can be controlled from a separate on-vehicle companion computer via a serial cable or wifi. The companion computer will usually communicate using a MAVLink API like the MAVSDK or MAVROS.












* Compass calibration on a drone is done to **align the drones’ flight system with the Earth’s magnetic north**, not its true north. This phenomena is known as _magnetic declination_ and accounts for the Earth’s shifting magnetic field (typically by a large number of degrees to that of true north). An algorithm stored in the rom memory of the aircraft accounts for this delta and allows for proper calibration of the magnetometer, the drone’s electronic compass. This magnetometer in conjunction with other onboard sources (GPS, gyros, accelerometer, altimeter) accurately determine its spatial positioning and are critical in generating precise flight control.
