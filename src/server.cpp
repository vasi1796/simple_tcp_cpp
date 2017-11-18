
#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace  std;
using namespace cv;
using boost::asio::ip::tcp;

Mat  img = Mat::zeros(640, 480, CV_8UC3);
bool flag = false;                              /* if flag is false ,the thread is not ready to show the mat frame */

void servershow()
{
    while (true)
    {
        if (flag)
        {
            imshow("server", img);
            waitKey(1);
        }
    }
}

int main()
{
    boost::thread thrd(&servershow);
    try
    {
        boost::asio::io_service io_service;
        boost::array<char, 921600> buf;         /* the size of received mat frame is calculated by width*height*no_channels */
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        for (;;)
        {
            boost::system::error_code error;
            size_t len = boost::asio::read(socket, boost::asio::buffer(buf), error);

            cout << "get data length :" << len << endl; /* disp the data size recieved */
            std::vector<uchar> vectordata(buf.begin(), buf.end()); /* change the recieved mat frame(1*buffer) to vector */
            cv::Mat data_mat(vectordata, true);

            img = data_mat.reshape(3, 480);       /* reshape to 3 channel and number of rows */
            cout << "reshape over" << endl;
            flag = true;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    thrd.join();
    return 0;
}
