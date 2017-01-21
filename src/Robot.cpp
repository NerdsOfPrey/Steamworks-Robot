#include <iostream>
#include <memory>
#include <string>
#include <CANTalon.h>
#include <RobotDrive.h>
#include <WPILib.h>
#include <Joystick.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <AHRS.h>

class Robot: public frc::IterativeRobot {
public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		frontLeftMotor = new CANTalon(1);
		frontRightMotor = new CANTalon(2);
		backLeftMotor = new CANTalon(3);
		backRightMotor = new CANTalon(4);

		myDrive = new RobotDrive(frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor);

		controller = new Joystick(0);


		ahrs = new AHRS(SPI::Port::kMXP);



	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *`	1`
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {
		SmartDashboard::PutNumber(  "IMU_TotalYaw", ahrs->GetAngle());
		SmartDashboard::PutNumber(  "IMU_Accel_X",          ahrs->GetWorldLinearAccelX());
		SmartDashboard::PutNumber(  "IMU_Accel_Y",          ahrs->GetWorldLinearAccelY());

	}

	void TeleopPeriodic() {
		myDrive->TankDrive(controller->GetRawAxis(1), controller->GetRawAxis(3), true);







	}

	void TestPeriodic() {
		lw->Run();
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	CANTalon *frontLeftMotor;
	CANTalon *frontRightMotor;
	CANTalon *backLeftMotor;
	CANTalon *backRightMotor;
	RobotDrive *myDrive;
	frc::Joystick* controller;
	AHRS *ahrs;

};

START_ROBOT_CLASS(Robot)
