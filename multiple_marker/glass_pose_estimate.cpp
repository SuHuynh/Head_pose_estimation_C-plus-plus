#include <opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <windows.h> // for unity
#include <math.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#define PI 3.14159265

#define BUF_SIZE 512
char szName[] = TEXT("headMmf");

using namespace cv;
using namespace std;
using namespace rs2;


int main(int argc, char** argv)
{

	// for unity
	// Create 
	HANDLE hMapFile;
	LPVOID pBuf;
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == NULL)
	{
		printf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		system("pause");
		return 1;
	}
	pBuf = MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		printf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);
		system("pause");
		return 1;
	}
	double head_info[6] = { 0 };
	//double head_init[6] = { 0 };
	bool init_flag = false;


	cv::String window_name;
	window_name = "Display Image";
	namedWindow(window_name, WINDOW_NORMAL);

	//Mat markerImage;
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_250);

	VideoCapture cap(0); //capture the video from web cam

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	while (true)
	{
		clock_t now_t;
		now_t = clock();

		Mat rbg_image;

		bool bSuccess = cap.read(rbg_image); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		// covert from BGR --> RGB image
		//cv::Mat rbg_image;
		//cv::cvtColor(frame, rbg_image, cv::COLOR_BGR2RGB);

		// Detect marker
		std::vector<int> markerIds, tmpIds;
		std::vector<std::vector<cv::Point2f>> markerCorners, tmpCorners;

		cv::Ptr<cv::aruco::DetectorParameters> parameters;
		cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << 812.15, 0.0, 328.26, 0.0, 814.72, 258.13, 0.0, 0.0, 1.0);
		cv::Mat dist_coeffs = (cv::Mat_<double>(5, 1) << -1.16, 1.96, 0.0, 0.0, -7.12);

		cv::aruco::detectMarkers(rbg_image, dictionary, tmpCorners, tmpIds);
		cout << "number of markers:" << tmpIds.size() << "\n";

		if (tmpIds.size() > 1)
		{

			cv::aruco::drawDetectedMarkers(rbg_image, tmpCorners, tmpIds);

			// code for multiple marker with un-sort

			std::vector<cv::Point2d> image_points;
			std::vector<cv::Point3d> w3D_points;

			for (int i = 0; i < tmpIds.size(); i++)
			{

				if (tmpIds[i] == 1)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(-72.05f, -2.37f, -22.55f));
					w3D_points.push_back(cv::Point3d(-72.05f, -2.37f, -37.55f));
					w3D_points.push_back(cv::Point3d(-87.05f, -2.44f, -37.55f));
					w3D_points.push_back(cv::Point3d(-87.05f, -2.44f, -22.55f));
				}

				if (tmpIds[i] == 10)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(7.5f, -7.5f, 0.0f));
					w3D_points.push_back(cv::Point3d(-7.5f, -7.5f, 0.0f));
					w3D_points.push_back(cv::Point3d(-7.5f, 7.5f, 0.0f));
					w3D_points.push_back(cv::Point3d(7.5f, 7.5f, 0.0f));
				}

				if (tmpIds[i] == 16)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(-78.13f, -0.40f, -7.53f));
					w3D_points.push_back(cv::Point3d(-87.77f, -0.44f, -19.02f));
					w3D_points.push_back(cv::Point3d(-87.84f, 14.56f, -19.02f));
					w3D_points.push_back(cv::Point3d(-78.19f, 14.60f, -7.53f));
				}

				if (tmpIds[i] == 24)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(-89.06f, -0.44f, -22.55f));
					w3D_points.push_back(cv::Point3d(-89.06f, -0.44f, -37.55f));
					w3D_points.push_back(cv::Point3d(-89.12f, 14.56f, -37.55));
					w3D_points.push_back(cv::Point3d(-89.12f, 14.56f, -22.55f));
				}

				if (tmpIds[i] == 32)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(-88.38f, -0.44f, -41.43f));
					w3D_points.push_back(cv::Point3d(-83.24f, -0.44f, -55.53f));
					w3D_points.push_back(cv::Point3d(-83.24f, 14.58f, -55.53f));
					w3D_points.push_back(cv::Point3d(-88.38f, 14.58f, -41.43f));
				}

				if (tmpIds[i] == 27)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(62.89f, 11.94f, 27.71f));
					w3D_points.push_back(cv::Point3d(47.89f, 11.87f, 27.71f));
					w3D_points.push_back(cv::Point3d(47.83f, 26.75f, 26.81f));
					w3D_points.push_back(cv::Point3d(62.83f, 26.82f, 26.81f));
				}

				if (tmpIds[i] == 201)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(-10.0f, 10.0f, 0.0f));
					w3D_points.push_back(cv::Point3d(10.0f, 10.0f, 0.0f));
					w3D_points.push_back(cv::Point3d(10.0f, -10.0f, 0.0f));
					w3D_points.push_back(cv::Point3d(-10.0f, -10.0f, 0.0f));
				}

				if (tmpIds[i] == 221)
				{
					image_points.push_back(tmpCorners[i][0]);
					image_points.push_back(tmpCorners[i][1]);
					image_points.push_back(tmpCorners[i][2]);
					image_points.push_back(tmpCorners[i][3]);

					w3D_points.push_back(cv::Point3d(14.5f, 10.0f, 4.0f));
					w3D_points.push_back(cv::Point3d(14.5f, 10.0f, 19.0f));
					w3D_points.push_back(cv::Point3d(14.5f, -10.0f, 19.0f));
					w3D_points.push_back(cv::Point3d(14.5f, -10.0f, 4.0f));
				}

			}


			Mat rotation_vector(1, 3, cv::DataType<double>::type);
			Mat translation_vector(1, 3, cv::DataType<double>::type);

			// Solve for pose
			solvePnP(w3D_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector, 0, 0);

			// estimate pose using Aruco lib
			/*cv::aruco::estimatePoseSingleMarkers(markerCorners,
				17, camera_matrix, dist_coeffs, rotation_vector, translation_vector);*/
		
			//drawAxis using Aruco lib

			cv::aruco::drawAxis(rbg_image, camera_matrix, dist_coeffs, rotation_vector, translation_vector, 50);

			// swap between x rotation and z rotation
			double tmp;
			tmp = rotation_vector.at<double>(0, 0);
			rotation_vector.at<double>(0, 0) = rotation_vector.at<double>(0, 2);
			rotation_vector.at<double>(0, 2) = tmp;

			// Send data to unity
			cv::Vec3f head_angle = Vec3f(rotation_vector) * 180 / PI;
			Mat translation_vector_m = translation_vector / 1000;
			/*for (int i = 0; i < 3; i++)
			{
				
				if (head_angle[i] > 180)
				{

				}

			}*/

			


			if (!init_flag)
			{
				for (int i = 0; i < 3; i++)
				{
					head_info[i] = head_angle[i];
				}
				for (int i = 3; i < 6; i++)
				{
					head_info[i] = translation_vector_m.at<double>(i - 3, 0);
				}
			}
			cout << "rotation_vector (don vi radian): " << rotation_vector;
			cout << "angle (don vi do): " << head_angle;
			cout << "translataion: " << translation_vector_m;
			CopyMemory(pBuf, head_info, (sizeof(head_info)));

		}

		clock_t dt = clock() - now_t;
		std::ostringstream title;
		title << " FPS:" << 1000.0 / dt << ", Init:" << "\n";
		setWindowTitle(window_name, cv::String(title.str()));

		cv::imshow(window_name, rbg_image);
		waitKey(1);
		//if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		//{
		//	cout << "esc key is pressed by user" << endl;
		//	break;
		//}

	}

	UnmapViewOfFile(pBuf); // remove the buffer 

	cvDestroyAllWindows();

	return 0;
}
