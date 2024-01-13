//https://github.com/micbelgique/YoloCSharp/blob/master/src/YoloApi/YoloApi.cpp
#include "yolo_v2_class.hpp"
#include <opencv2/opencv.hpp>
#include<malloc.h>

#if defined(_WINDOWS)
#define YOLOAPI_EXPORT __declspec(dllexport)
#else
#define YOLOAPI_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
	static Detector* instance = NULL;

	/**
	 * Purpose: Initializes a new instance of the Darknet detector
	 *
	 * @param cfg_filename Relative path to the config file
	 * @param weight_filename Relative path to the weights file
	 * @param gpu_id The CUDA compatible GPU index
	 */
	YOLOAPI_EXPORT void initDetector(char* cfg_filename, char* weight_filename, int gpu_id) {
		instance = new Detector(std::string(cfg_filename), std::string(weight_filename), gpu_id);
	}

	/**
	 * Purpose: Destroys the Darknet detector instance, ready to be re-initialized
	 */
	YOLOAPI_EXPORT void closeDetector() {
		if (instance != NULL) {
			delete instance;
			instance = NULL;
		}
	}

	/**
	 * Purpose: Launches the detection process on a cv::Mat object and returns its bounding boxes
	 *
	 * @param mat_data Pointer to a cv::Mat object (8 bits & 3 channels) containing the frame to be processed
	 * @param mat_rows Rows of the cv::Mat object
	 * @param mat_cols Columns of the cv::Mat object
	 * @param thresh Threshold at which to detect objects
	 * @param use_mean
	 * @param elems Returned bounding boxes of each detected object on an image (out)
	 * @param array_size Amount of objects detected on the image (out)
	 */
	YOLOAPI_EXPORT bbox_t* detect(cv::Mat *img_mat, float thresh, bool use_mean, int* elems_size) {
		//cv::Mat img_mat = cv::Mat(mat_rows, mat_cols, CV_8UC3, mat_data);		
		printf("element size passed in =%i\n", *elems_size);

		std::vector<bbox_t> result_vector = instance->detect(*img_mat, thresh, use_mean);
		//*elems = result_vector.data();

		int copyLen = result_vector.size();
		printf("Done, result size =%i, element size =%i\n", copyLen, sizeof(bbox_t));
		bbox_t* elems = (bbox_t *)malloc(sizeof(bbox_t) * copyLen);
		printf("malloc %llux%i %i\n", sizeof(bbox_t), copyLen, (int)elems);
		if (elems != NULL) {
			for (int i = 0; i < copyLen; i++) {
				elems[i].h = 0;				
				memcpy(elems + i, result_vector.data() + i, sizeof(bbox_t));
				//elems[i] = result_vector[i];
			}
		}
		*elems_size = result_vector.size();
		printf("Done, result len %llu\n", result_vector.size());
		return elems;
	}

	YOLOAPI_EXPORT void freeDetectData(bbox_t* data) {
		free(data);
	}
}
