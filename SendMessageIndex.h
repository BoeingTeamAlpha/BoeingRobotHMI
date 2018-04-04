#ifndef SENDMESSAGEINDEX_H
#define SENDMESSAGEINDEX_H

struct SendMessageIndex
{
	enum Enum
	{
		LeftDriveMotor		= 1,
		RightDriveMotor		= 3,
		CameraLeftRight		= 5,
		DumpBedRaiseLower	= 7,
		GripperRaiseLower	= 9,
		GripperOpenClose	= 11,
		NUM_INDEX
	};
};

#endif // SENDMESSAGEINDEX_H
