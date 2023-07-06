#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

static void mouseHandler(int event, int x, int y, int flags, void* param) {
	if (event == cv::EVENT_LBUTTONDOWN) {
		cv::Point* p = (cv::Point*)param;
		p->x = x;
		p->y = y;
	}
}

#include <vector>
void  test(cv::Mat srcImg, cv::Mat& dstImg, std::vector<std::vector<cv::Point>> vec_points) {
	if (vec_points.size() < 4)
	{
		cv::Point2f coordinates[4];

		for (size_t i = 0; i < vec_points.size(); i++)
		{
			for (size_t j = 0; j < vec_points[i].size(); j++)
			{
				coordinates[i] = vec_points[i][j];
			}
			//coordinates->y = (float)vec_points[i][1];
			std::cout << coordinates[i].x << std::endl;
			std::cout << coordinates[i].y << std::endl;
		}

		float w = coordinates[1].x - coordinates[0].x;
		float h = ((coordinates[2].y - coordinates[0].y) + (coordinates[3].y - coordinates[1].y)) / 2;

		if (w / 4.7f < h) w = h * 4.7f;


		cv::Point2f dst[4] = { { 0.0f, 0.0f }, { w, 0.0f }, { 0.0f, h }, { w, h } };

		cv::Mat matrix = cv::getPerspectiveTransform(coordinates, dst);
		//cv::Mat imgWarp;

		cv::warpPerspective(srcImg, dstImg, matrix, cv::Point(w, h));

		//cv::imshow("frame", srcImg);
		//cv::imshow("frame2", imgWarp);
		//cv::waitKey(0);
	}
	else return;
	

}

int main() {

	//float w = 700.0f;
	//float h = 200.0f;

	cv::Mat mat = cv::imread("D:\\projects2\\dynamicSize\\4.jpg");

	cv::Point2f src[4];// = { { 221, 211 }, { 740, 555 }, { 598, 367 }, { 209, 401 } };

	for (int i = 0; i < 4; ++i) {

		cv::Point p;

		cv::imshow("test", mat);
		setMouseCallback("test", mouseHandler, &p);
		cv::waitKey(0);

		//p6[i].x = p.x;
		//p6[i].y = p.y;
		/*src_p[i].x = p.x;
		src_p[i].y = p.y;
		i++;*/

		std::cout << p.x << ": " << p.y << std::endl;
		if (i == 2)
		{
			src[3].x = p.x;
			src[3].y = p.y;
		}
		else if (i == 3)
		{
			src[2].x = p.x;
			src[2].y = p.y;
		}
		else
		{
			src[i].x = p.x;
			src[i].y = p.y;
		}		
	}

	float w = src[1].x - src[0].x;
	float h = ((src[2].y - src[0].y) + (src[3].y - src[1].y)) / 2;

	if (w / 4.7f < h) w = h * 4.7f;


	cv::Point2f dst[4] = { { 0.0f, 0.0f }, { w, 0.0f }, { 0.0f, h }, { w, h } };
	std::cout << "p1 " << dst[0].x << "," << dst[0].y << std::endl;
	std::cout << "p2 " << dst[1].x << "," << dst[1].y << std::endl;
	std::cout << "p3 " << dst[2].x << "," << dst[2].y << std::endl;
	std::cout << "p4 " << dst[3].x << "," << dst[3].y << std::endl;

	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	cv::Mat imgWarp;

	cv::warpPerspective(mat, imgWarp, matrix, cv::Point(w, h));
	cv::circle(imgWarp, cv::Point(dst[0].x, dst[0].y), 4, cv::Scalar(255, 0, 0), cv::LINE_8);
	cv::circle(imgWarp, cv::Point(dst[1].x, dst[1].y), 4, cv::Scalar(0, 255, 0), cv::LINE_8);
	cv::circle(imgWarp, cv::Point(dst[2].x, dst[2].y), 4, cv::Scalar(0, 0, 255), cv::LINE_8);
	cv::circle(imgWarp, cv::Point(dst[3].x, dst[3].y), 4, cv::Scalar(255, 255, 255), cv::LINE_8);

	cv::circle(mat, cv::Point(src[0].x, src[0].y), 4, cv::Scalar(255, 0, 0), cv::LINE_8);
	cv::circle(mat, cv::Point(src[1].x, src[1].y), 4, cv::Scalar(0, 255, 0), cv::LINE_8);
	cv::circle(mat, cv::Point(src[2].x, src[2].y), 4, cv::Scalar(0, 0, 255), cv::LINE_8);
	cv::circle(mat, cv::Point(src[3].x, src[3].y), 4, cv::Scalar(255, 255, 255), cv::LINE_8);

	std::cout << "p1 " << src[0].x << "," << src[0].y << std::endl;
	std::cout << "p2 " << src[1].x << "," << src[1].y << std::endl;
	std::cout << "p3 " << src[2].x << "," << src[2].y << std::endl;
	std::cout << "p4 " << src[3].x << "," << src[3].y << std::endl;
	cv::imshow("frame", mat);
	cv::imshow("frame2", imgWarp);
	cv::waitKey(0);
}