#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

// устанавливаем границы цвета (в HSV формате) построения маски 
int lower_Sat = 1;
int lower_Vat = 1;
int upper_Sat = 255;
int upper_Vat = 255;

int lower_red_Hue_1 = 1;
int upper_red_Hue_1 = 16;

int lower_orange_Hue = 17;
int upper_orange_Hue = 47;

int lower_yellow_Hue = 48;
int upper_yellow_Hue = 79;

int lower_green_Hue = 80;
int upper_green_Hue = 111;

int lower_aqua_Hue = 112;
int upper_aqua_Hue = 143;

int lower_blue_Hue = 144;
int upper_blue_Hue = 175;

int lower_purple_Hue = 176;
int upper_purple_Hue = 207;

int lower_pink_Hue = 208;
int upper_pink_Hue = 239;

int lower_red_Hue_2 = 240;
int upper_red_Hue_2 = 254;

// define range of white color in HSV
int lower_white_Hue = 0;
int lower_white_Sat = 0;
int lower_white_Vat = 235;
int upper_white_Hue = 255;
int upper_white_Sat = 20;
int upper_white_Vat = 255;

// define range of black color in HSV
int lower_black_Hue = 0;
int lower_black_Sat = 235;
int lower_black_Vat = 0;
int upper_black_Hue = 255;
int upper_black_Sat = 255;
int upper_black_Vat = 20;


// Функция высчитывает процентное содержание цвета
double Percent_target_color(Mat frame_copy, string target_color)
{
	double percent = 0.0; // нужный процент содержания искомого обьекта в кадре
	bool filling_color = false; // содержание цвета целевого обьекта в области должно быть >= percent%

	Mat mask_white_copy;
	Mat mask_black_copy;
	Mat mask_red_1_copy;
	Mat mask_orange_copy;
	Mat mask_yellow_copy;
	Mat mask_green_copy;
	Mat mask_aqua_copy;
	Mat mask_blue_copy;
	Mat mask_purple_copy;
	Mat mask_pink_copy;
	Mat mask_red_2_copy;

	int color_percent_white;
	int color_percent_black;
	int color_percent_red;
	int color_percent_orange;
	int color_percent_yellow;
	int color_percent_green;
	int color_percent_aqua;
	int color_percent_blue;
	int color_percent_purple;
	int color_percent_pink;

	int img_razm;
	int color_HSV[10];
	int color_HSV_izn[10]; // не отсортированный массив, нужен для определения цветов в отсортированном массиве
	string color_named[10] = { "white", "black", "orange", "yellow", "green", "aqua", "blue", "purple", "pink", "red" };
	Mat HSV_Frame_copy;

	frame_copy.convertTo(frame_copy, -1, 1, 1);
	// Конвертирование кадра в HSV формат 
	cvtColor(frame_copy, HSV_Frame_copy, COLOR_BGR2HSV);

	// Высчитываем цветовые маски
	// HSV  маска для белого цвета
	inRange(HSV_Frame_copy, Scalar(lower_white_Hue, lower_white_Sat, lower_white_Vat), Scalar(upper_white_Hue, upper_white_Sat, upper_white_Vat), mask_white_copy);
	color_percent_white = countNonZero(mask_white_copy);
	color_HSV[0] = color_percent_white;
	color_HSV_izn[0] = color_percent_white;
	// HSV  маска для черного цвета
	inRange(HSV_Frame_copy, Scalar(lower_black_Hue, lower_black_Sat, lower_black_Vat), Scalar(upper_black_Hue, upper_black_Sat, upper_black_Vat), mask_black_copy);
	color_percent_black = countNonZero(mask_black_copy);
	color_HSV[1] = color_percent_black;
	color_HSV_izn[1] = color_percent_black;
	// HSV  маска для красного_1 цвета
	inRange(HSV_Frame_copy, Scalar(lower_red_Hue_1, lower_Sat, lower_Vat), Scalar(upper_red_Hue_1, upper_Sat, upper_Vat), mask_red_1_copy);
	color_percent_red = countNonZero(mask_red_1_copy);
	// HSV  маска для оранжевого цвета
	inRange(HSV_Frame_copy, Scalar(lower_orange_Hue, lower_Sat, lower_Vat), Scalar(upper_orange_Hue, upper_Sat, upper_Vat), mask_orange_copy);
	color_percent_orange = countNonZero(mask_orange_copy);
	color_HSV[2] = color_percent_orange;
	color_HSV_izn[2] = color_percent_orange;
	// HSV  маска для желтого цвета
	inRange(HSV_Frame_copy, Scalar(lower_yellow_Hue, lower_Sat, lower_Vat), Scalar(upper_yellow_Hue, upper_Sat, upper_Vat), mask_yellow_copy);
	color_percent_yellow = countNonZero(mask_yellow_copy);
	color_HSV[3] = color_percent_yellow;
	color_HSV_izn[3] = color_percent_yellow;
	// HSV  маска для зеленого цвета
	inRange(HSV_Frame_copy, Scalar(lower_green_Hue, lower_Sat, lower_Vat), Scalar(upper_green_Hue, upper_Sat, upper_Vat), mask_green_copy);
	color_percent_green = countNonZero(mask_green_copy);
	color_HSV[4] = color_percent_green;
	color_HSV_izn[4] = color_percent_green;
	// HSV  маска для голобуго цвета
	inRange(HSV_Frame_copy, Scalar(lower_aqua_Hue, lower_Sat, lower_Vat), Scalar(upper_aqua_Hue, upper_Sat, upper_Vat), mask_aqua_copy);
	color_percent_aqua = countNonZero(mask_aqua_copy);
	color_HSV[5] = color_percent_aqua;
	color_HSV_izn[5] = color_percent_aqua;
	// HSV  маска для синего цвета
	inRange(HSV_Frame_copy, Scalar(lower_blue_Hue, lower_Sat, lower_Vat), Scalar(upper_blue_Hue, upper_Sat, upper_Vat), mask_blue_copy);
	color_percent_blue = countNonZero(mask_blue_copy);
	color_HSV[6] = color_percent_blue;
	color_HSV_izn[6] = color_percent_blue;
	// HSV  маска для фиолетового цвета
	inRange(HSV_Frame_copy, Scalar(lower_purple_Hue, lower_Sat, lower_Vat), Scalar(upper_purple_Hue, upper_Sat, upper_Vat), mask_purple_copy);
	color_percent_purple = countNonZero(mask_purple_copy);
	color_HSV[7] = color_percent_purple;
	color_HSV_izn[7] = color_percent_purple;
	// HSV  маска для розового цвета
	inRange(HSV_Frame_copy, Scalar(lower_pink_Hue, lower_Sat, lower_Vat), Scalar(upper_pink_Hue, upper_Sat, upper_Vat), mask_pink_copy);
	color_percent_pink = countNonZero(mask_pink_copy);
	color_HSV[8] = color_percent_pink;
	color_HSV_izn[8] = color_percent_pink;
	// HSV  маска для красного_2 цвета
	inRange(HSV_Frame_copy, Scalar(lower_red_Hue_2, lower_Sat, lower_Vat), Scalar(upper_red_Hue_2, upper_Sat, upper_Vat), mask_red_2_copy);
	color_percent_red = color_percent_red + countNonZero(mask_red_2_copy);
	color_HSV[9] = color_percent_red;
	color_HSV_izn[9] = color_percent_red;

	// Высчитываем размер изображения
	int rows = frame_copy.rows;
	int cols = frame_copy.cols;
	img_razm = rows * cols;

	// Меняем значение количества пикселей в массиве на процентное содержание цвета
	for (int i = 0; i <= 9; ++i)
	{
		//cout << "HSV: " << color_HSV[i] * 100.0 / img_razm << " color:" << color_named[i] << " in: " << img_razm << endl;
	}
	// Сравниваем процентное содержание цвета целевого обьекта в исследуемой области с требуемой процентой точностью
	for (int i = 0; i <= 9; ++i)
	{
		if (color_named[i] == target_color)
		{
			percent = color_HSV[i] * 100.0 / img_razm;
			return percent;
		}
	}

	return percent;
}


// Функция проверяет контрастность color и big_color, используя теорию цветового круга
int contrast_color(string color, string big_color)
{
	int contrast = 0;
	if (color == "white") { contrast = 1; }
	else if (color == "black") { contrast = 1; }
	else if (color == "orange") { if (big_color == "red" || big_color == "yellow") { contrast = 0; } else { contrast = 1; } }
	else if (color == "yellow") { if (big_color == "orange" || big_color == "red") { contrast = 0; } else { contrast = 1; } }
	else if (color == "green") { if (big_color == "aqua" || big_color == "blue") { contrast = 0; } else { contrast = 1; } }
	else if (color == "aqua") { if (big_color == "blue" || big_color == "green") { contrast = 0; } else { contrast = 1; } }
	else if (color == "blue") { if (big_color == "aqua" || big_color == "green") { contrast = 0; } else { contrast = 1; } }
	else if (color == "purple") { if (big_color == "pink" || big_color == "red") { contrast = 0; } else { contrast = 1; } }
	else if (color == "pink") { if (big_color == "purple" || big_color == "red") { contrast = 0; } else { contrast = 1; } }
	else if (color == "red") { if (big_color == "orange" || big_color == "yellow") { contrast = 0; } else { contrast = 1; } }
	else if (color == "none") { contrast = 2; }

	return contrast;
}

// Вырезает обьект по контуру цвета целевого обьекта и сохраняет в файлы
void Cut_tile(Mat tile, string color, int number_object)
{
	cvtColor(tile, tile, COLOR_BGR2BGRA); // переводим фрагмент в формат с каналом прозрачности
	// Высчитываем размер изображения
	int rows = tile.rows;
	int cols = tile.cols;
	// Формирование названия файла для хранения обьекта
	string name = "name_";
	string number = to_string(number_object);
	string extension = ".png";
	string full_name = name + number + extension;
	// для нахождения контура
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat HSV_cut_obj; // маска
	Mat HSV_tile;
	cvtColor(tile, HSV_tile, COLOR_BGR2HSV);
	// Строим HSV маску в фрагменте по цвету целевого обьекта
	if (color == "white") { inRange(HSV_tile, Scalar(lower_white_Hue, lower_white_Sat, lower_white_Vat), Scalar(upper_white_Hue, upper_white_Sat, upper_white_Vat), HSV_cut_obj); }
	else if (color == "black") { inRange(HSV_tile, Scalar(lower_black_Hue, lower_black_Sat, lower_black_Vat), Scalar(upper_black_Hue, upper_black_Sat, upper_black_Vat), HSV_cut_obj); }
	else if (color == "orange") { inRange(HSV_tile, Scalar(lower_orange_Hue, lower_Sat, lower_Vat), Scalar(upper_orange_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "yellow") { inRange(HSV_tile, Scalar(lower_yellow_Hue, lower_Sat, lower_Vat), Scalar(upper_yellow_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "green") { inRange(HSV_tile, Scalar(lower_green_Hue, lower_Sat, lower_Vat), Scalar(upper_green_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "aqua") { inRange(HSV_tile, Scalar(lower_aqua_Hue, lower_Sat, lower_Vat), Scalar(upper_aqua_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "blue") { inRange(HSV_tile, Scalar(lower_blue_Hue, lower_Sat, lower_Vat), Scalar(upper_blue_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "purple") { inRange(HSV_tile, Scalar(lower_purple_Hue, lower_Sat, lower_Vat), Scalar(upper_purple_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "pink") { inRange(HSV_tile, Scalar(lower_pink_Hue, lower_Sat, lower_Vat), Scalar(upper_pink_Hue, upper_Sat, upper_Vat), HSV_cut_obj); }
	else if (color == "red") { inRange(HSV_tile, Scalar(lower_red_Hue_1, lower_Sat, lower_Vat), Scalar(upper_red_Hue_1, upper_Sat, upper_Vat), HSV_cut_obj); }
	// Находим контур по построенной маске
	findContours(HSV_cut_obj, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	// Замена фона на прозрачный
	Mat mask = Mat::zeros(HSV_cut_obj.rows, HSV_cut_obj.cols, CV_8UC1);
	// Заполняем область внутри контура - формируем маску, по которой будет отделен обьект от фона
	drawContours(mask, contours, -1, Scalar(255), -1);
	Mat crop(tile.rows, tile.cols, CV_8UC4); // инициализация фона, на который будет нанесен обьект
	crop.setTo(Scalar(0, 0, 0, 0)); // заполнение прозрачным фоном
	tile.copyTo(crop, mask); // добавление обьекта на новый фон

	// Выявление границ и вырезание обьекта для того чтобы в файл попало как можно меньше фона
	Point max[1000];
	for (int i = 0; i < 1000; i++)
	{
		max[i].x = -1;
		max[i].y = -1;
	}
	int k = 0;
	//Point max =max_element(contours.begin(), contours.end());
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++) // run until j < contours[i].size();
		{
			max[k] = contours[i][j];
			k += 1;
		}
	}
	float min_x = 1920;
	float max_x = 0;
	float min_y = 1920;
	float max_y = 0;

	for (int i = 0; i < 1000; i++)
	{
		if (max[i].x != -1 && max[i].y != -1)
		{
			if (max[i].x < min_x)
			{
				min_x = max[i].x;
			}
			if (max[i].x > max_x)
			{
				max_x = max[i].x;
			}
			if (max[i].y < min_y)
			{
				min_y = max[i].y;
			}
			if (max[i].y > max_y)
			{
				max_y = max[i].y;
			}
		}
	}
	Mat cropped_image = crop(Range(min_y, max_y), Range(min_x, max_x));
	// Сохраняем обьект в файл
	imwrite(full_name, cropped_image);
}

// Функция обработки кадра (формирование рамки области интереса; Нахождение обьекта в области интереса ; выделение границ области области самым распространенным цветом в HSV формате)
Mat Processing_frame(Mat frame, Mat HSV_Frame, string target_color, string color_named)
{
	Mat tile; // фрагмент
	Mat fragment[50]; // сохраняем нужные фрагменты
	int segment_size = 300; // размер tile(нарезанного фрагмента кадра) сегмента 
	Point2f points[4]; // координаты крайних точек фрагмента
	int number_object = 1; // индекс сохраненного фрагмента
	double percent; // процент цвета целевого обьекта, который был найден в нарезанном фрагменте
	Mat frame_copy; // копируем кадр для дальнейшей работы над ним
	frame.copyTo(frame_copy);
	// Высчитываем размер изображения
	int rows = frame.rows;
	int cols = frame.cols;
	int safe_obj = 0; // индекс найденного обьекта
	// для нахождения контура
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Mat mask_HSV;
	Mat HSV_tile;
	Mat tile_copy;
	// Размер фрагмента
	int row;
	int col;
	int B, G, R; // цвет рамки области и контура обьектов исходя их самого распространенного цвета в HSV формате
	for (int r = 0; r < rows; r += segment_size)
	{
		for (int c = 0; c < cols; c += segment_size)
		{
			tile = frame(Range(r, min(r + segment_size, rows)), Range(c, min(c + segment_size, cols)));
			tile.copyTo(tile_copy);
			cvtColor(tile, HSV_tile, COLOR_BGR2HSV);
			percent = Percent_target_color(tile, target_color);
			if (percent > 0.15)
			{
				points[0] = (Point2f(c, r));
				points[1] = (Point2f(min(c + segment_size, cols), r));
				points[2] = (Point2f(min(c + segment_size, cols), min(r + segment_size, rows)));
				points[3] = (Point2f(c, min(r + segment_size, rows)));
				// Сохраняем сам фрагмент
				fragment[number_object] = tile;
				row = tile.rows; // размер фрагмента 
				col = tile.cols;
				if (color_named == "white") { B = 255; G = 255; R = 255; }
				else if (color_named == "black") { B = 0; G = 0; R = 0; }
				else if (color_named == "red") { B = 0; G = 0; R = 255; }
				else if (color_named == "orange") { B = 0; G = 165; R = 255; }
				else if (color_named == "yellow") { B = 0; G = 255; R = 255; }
				else if (color_named == "green") { B = 0; G = 255; R = 0; }
				else if (color_named == "aqua") { B = 255; G = 170; R = 66; }
				else if (color_named == "blue") { B = 255; G = 0; R = 0; }
				else if (color_named == "purple") { B = 255; G = 0; R = 139; }
				else if (color_named == "pink") { B = 203; G = 192; R = 255; }
				// Рисование квадратной рамки вокруг выделенного, нарезанного фрагмента
				if (target_color == "white")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_white_Hue, lower_white_Sat, lower_white_Vat), Scalar(upper_white_Hue, upper_white_Sat, upper_white_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "black")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_black_Hue, lower_black_Sat, lower_black_Vat), Scalar(upper_black_Hue, upper_black_Sat, upper_black_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
				}
				else if (target_color == "red")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_red_Hue_1, lower_Sat, lower_Vat), Scalar(upper_red_Hue_1, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "orange")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_orange_Hue, lower_Sat, lower_Vat), Scalar(upper_orange_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "yellow")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_yellow_Hue, lower_Sat, lower_Vat), Scalar(upper_yellow_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "green")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_green_Hue, lower_Sat, lower_Vat), Scalar(upper_green_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (color_named == "aqua") 
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_aqua_Hue, lower_Sat, lower_Vat), Scalar(upper_aqua_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "blue")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_blue_Hue, lower_Sat, lower_Vat), Scalar(upper_blue_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "purple")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_purple_Hue, lower_Sat, lower_Vat), Scalar(upper_purple_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(frame_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				else if (target_color == "pink")
				{
					line(frame_copy, points[0], points[1], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[1], points[2], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[2], points[3], Scalar(B, G, R), 2, LINE_8);
					line(frame_copy, points[3], points[0], Scalar(B, G, R), 2, LINE_8);
					inRange(HSV_tile, Scalar(lower_pink_Hue, lower_Sat, lower_Vat), Scalar(upper_pink_Hue, upper_Sat, upper_Vat), mask_HSV);
					// Рисование контура обьекта в фрагменте
					findContours(mask_HSV, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
					drawContours(tile_copy, contours, -1, Scalar(B, G, R), 2);
					tile_copy.copyTo(frame_copy(Rect(points[0], Size(row, col))));
				}
				Cut_tile(tile, target_color, safe_obj); // вырезаем и сохраняем найденный обьект
				number_object += 1;
				safe_obj += 1;
			}
		}
	}
	return frame_copy;
}


int main(void) 
{

	//VideoCapture cap("C:\\CV\\Practic\\2022-10-06 15-25-30.mp4");
	VideoCapture cap("C:\\CV\\Practic\\1000.mp4");

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}


	int sec = 4; // нужна для того чтобы выполнять некоторые функции раз в 5 секунд
	int b;
	int g;
	int r;
	String window_name = "Analise";
	double fps;
	// переменные отвечают за содержание цвета в кадре (попиксельно)
	int color_percent_white;
	int color_percent_black;
	int color_percent_red;
	int color_percent_orange;
	int color_percent_yellow;
	int color_percent_green;
	int color_percent_aqua;
	int color_percent_blue;
	int color_percent_purple;
	int color_percent_pink;
	// поиск цвета целевого обьекта
	int img_razm;
	int color_HSV[10];
	int color_HSV_izn[10]; // не отсортированный массив, нужен для определения цветов в отсортированном массиве
	string color_named[10] = { "white", "black", "orange", "yellow", "green", "aqua", "blue", "purple", "pink", "red" };
	int max = 0;
	string target_color; //  цвет целевого обьекта
	bool find_target_color = false; // найден ли первый из массива цвет целевого обькта (переменная нужна для выхода из внешнего цикла)
	int ball_contrast = 0; // количество цветов к которым контрастен предпалагаемый цвет целевого обьекта
	// массив содержит цвета, относящиеся к фону (занимают больше 30% кадра) - если условие не срабатывает, но за фон берется наиболее представленный цвет в кадре
	string big_color[10] = { "none", "none", "none", "none", "none", "none", "none", "none", "none", "none" };
	int find_big_color = 0; // найден ли цвет, занимающий более 30% от кадра - нужно для условия (по совместительству индекс массива big_color)

	int index = 0;
	// для нахлждения маски
	Mat frame;
	Mat HSV_Frame;
	Mat mask_white;
	Mat mask_black;

	Mat mask_red_1;
	Mat mask_orange;
	Mat mask_yellow;
	Mat mask_green;
	Mat mask_aqua;
	Mat mask_blue;
	Mat mask_purple;
	Mat mask_pink;
	Mat mask_red_2;

	bool firstRead = false;
	Point2f points[4];
	int rows, cols;
	int draw_HSV = 0; // рисовать (1) HSV маски на кадре или нет (0)

	// для нахождения контура
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	namedWindow(window_name, WINDOW_NORMAL); //create a window

	cap.read(frame);
	rows = frame.rows;
	cols = frame.cols;
	img_razm = rows * cols;

	int one = 0;

	while (true)
	{
		bool bSuccess = cap.read(frame);
		if (bSuccess == false)
		{
			cout << "Found the end of the video" << endl;
			break;
		}
		sec = sec + 1;

		frame.convertTo(frame, -1, 1, 1);
		// Конвертирование кадра в HSV формат 
		cvtColor(frame, HSV_Frame, COLOR_BGR2HSV);


		// HSV  маска для белого цвета
		inRange(HSV_Frame, Scalar(lower_white_Hue, lower_white_Sat, lower_white_Vat), Scalar(upper_white_Hue, upper_white_Sat, upper_white_Vat), mask_white);
		color_percent_white = countNonZero(mask_white);
		color_HSV[0] = color_percent_white;
		color_HSV_izn[0] = color_percent_white;
		//cout << "White: " << color_percent_white << endl;
		// HSV  маска для черного цвета
		inRange(HSV_Frame, Scalar(lower_black_Hue, lower_black_Sat, lower_black_Vat), Scalar(upper_black_Hue, upper_black_Sat, upper_black_Vat), mask_black);
		color_percent_black = countNonZero(mask_black);
		color_HSV[1] = color_percent_black;
		color_HSV_izn[1] = color_percent_black;
		//cout << "Black: " << color_percent_black << endl;
		// HSV  маска для красного_1 цвета
		inRange(HSV_Frame, Scalar(lower_red_Hue_1, lower_Sat, lower_Vat), Scalar(upper_red_Hue_1, upper_Sat, upper_Vat), mask_red_1);
		color_percent_red = countNonZero(mask_red_1);
		// HSV  маска для оранжевого цвета
		inRange(HSV_Frame, Scalar(lower_orange_Hue, lower_Sat, lower_Vat), Scalar(upper_orange_Hue, upper_Sat, upper_Vat), mask_orange);
		color_percent_orange = countNonZero(mask_orange);
		color_HSV[2] = color_percent_orange;
		color_HSV_izn[2] = color_percent_orange;
		//cout << "Orange: " << color_percent_orange << endl;
		// HSV  маска для желтого цвета
		inRange(HSV_Frame, Scalar(lower_yellow_Hue, lower_Sat, lower_Vat), Scalar(upper_yellow_Hue, upper_Sat, upper_Vat), mask_yellow);
		color_percent_yellow = countNonZero(mask_yellow);
		color_HSV[3] = color_percent_yellow;
		color_HSV_izn[3] = color_percent_yellow;
		//cout << "Yellow: " << color_percent_yellow << endl;
		// HSV  маска для зеленого цвета
		inRange(HSV_Frame, Scalar(lower_green_Hue, lower_Sat, lower_Vat), Scalar(upper_green_Hue, upper_Sat, upper_Vat), mask_green);
		color_percent_green = countNonZero(mask_green);
		color_HSV[4] = color_percent_green;
		color_HSV_izn[4] = color_percent_green;
		//cout << "Green: " << color_percent_green << endl;
		// HSV  маска для голобуго цвета
		inRange(HSV_Frame, Scalar(lower_aqua_Hue, lower_Sat, lower_Vat), Scalar(upper_aqua_Hue, upper_Sat, upper_Vat), mask_aqua);
		color_percent_aqua = countNonZero(mask_aqua);
		color_HSV[5] = color_percent_aqua;
		color_HSV_izn[5] = color_percent_aqua;
		//cout << "Aqua: " << color_percent_aqua << endl;
		// HSV  маска для синего цвета
		inRange(HSV_Frame, Scalar(lower_blue_Hue, lower_Sat, lower_Vat), Scalar(upper_blue_Hue, upper_Sat, upper_Vat), mask_blue);
		color_percent_blue = countNonZero(mask_blue);
		color_HSV[6] = color_percent_blue;
		color_HSV_izn[6] = color_percent_blue;
		//cout << "Blue: " << color_percent_blue << endl;
		// HSV  маска для фиолетового цвета
		inRange(HSV_Frame, Scalar(lower_purple_Hue, lower_Sat, lower_Vat), Scalar(upper_purple_Hue, upper_Sat, upper_Vat), mask_purple);
		color_percent_purple = countNonZero(mask_purple);
		color_HSV[7] = color_percent_purple;
		color_HSV_izn[7] = color_percent_purple;
		//cout << "Puple: " << color_percent_purple << endl;
		// HSV  маска для розового цвета
		inRange(HSV_Frame, Scalar(lower_pink_Hue, lower_Sat, lower_Vat), Scalar(upper_pink_Hue, upper_Sat, upper_Vat), mask_pink);
		color_percent_pink = countNonZero(mask_pink);
		color_HSV[8] = color_percent_pink;
		color_HSV_izn[8] = color_percent_pink;
		//cout << "Pink: " << color_percent_pink << endl;
		// HSV  маска для красного_2 цвета
		inRange(HSV_Frame, Scalar(lower_red_Hue_2, lower_Sat, lower_Vat), Scalar(upper_red_Hue_2, upper_Sat, upper_Vat), mask_red_2);
		color_percent_red = color_percent_red + countNonZero(mask_red_2);
		color_HSV[9] = color_percent_red;
		color_HSV_izn[9] = color_percent_red;
		//cout << "Red: " << color_percent_red << endl;

		// поиск цвета целевого обьекта раз в 5 кадров
		if (sec == 5)
		{
			color_named[0] = "white";
			color_named[1] = "black";
			color_named[2] = "orange";
			color_named[3] = "yellow";
			color_named[4] = "green";
			color_named[5] = "aqua";
			color_named[6] = "blue";
			color_named[7] = "purple";
			color_named[8] = "pink";
			color_named[9] = "red";

			big_color[0] = "none";
			big_color[1] = "none";
			big_color[2] = "none";
			big_color[3] = "none";
			big_color[4] = "none";
			big_color[5] = "none";
			big_color[6] = "none";
			big_color[7] = "none";
			big_color[8] = "none";
			big_color[9] = "none";

			// сортировка цветов по возрастанию
			int temp = 0;
			string temp_string = "";
			for (int i = 0; i < 10; i++)
			{
				for (int j = 9; j > i; j--) // для всех элементов после i-ого
				{
					if (color_HSV[j - 1] > color_HSV[j]) // если текущий элемент меньше предыдущего
					{
						temp = color_HSV[j - 1]; // меняем их местами
						color_HSV[j - 1] = color_HSV[j];
						color_HSV[j] = temp;

						temp_string = color_named[j - 1]; // меняем их местами
						color_named[j - 1] = color_named[j];
						color_named[j] = temp_string;
					}
				}
				temp = 0;
				temp_string = "";
			}
			// Поиск максимаьно представденного цвета в кадре
			for (int i = 0; i <= 9; ++i)
			{
				if (color_HSV[i] * 100.0 / img_razm >= 30)
				{
					big_color[find_big_color] = color_named[i];
					find_big_color += 1;
				}
			}
			if (find_big_color == 0)
			{
				for (int i = 0; i <= 9; ++i)
				{
					if (color_HSV[i] > max)
					{
						max = color_HSV[i];
						index = i;
					}
				}
				big_color[0] = color_named[index];
			}
			// подсчет количества фоновых  цветов
			find_big_color = 0;
			for (int i = 0; i <= 9; ++i)
			{
				if (big_color[i] != "none")
				{
					find_big_color += 1;
				}
			}
			// Вывод процента закрашенных пикселей по каждому цвету
			for (int i = 0; i <= 9; ++i)
			{
				cout << "HSV: " << color_HSV[i] * 100.0 / img_razm << " color:" << color_named[i] << endl;
			}
			// Поиск цвета целевого обьекта (он должен быть больше 0.025% по представлению в кадре и меньше 10% по представлению в кадре)
			for (int i = 0; i <= 9; ++i)
			{
				//cout << "color" << color_HSV[i] * 100.0 / img_razm << endl;
				if (color_HSV[i] * 100.0 / img_razm >= 0.025 && color_HSV[i] * 100.0 / img_razm <= 10)
				{
					// контрастен ли цвет с наиболее представлеными цветами в кадре?
					if (find_big_color - 1 >= 1)
					{
						for (int j = 0; j <= find_big_color - 1; ++j)
						{
							if (contrast_color(color_named[i], big_color[j]) == 1)
							{
								//cout << "Target_color: " << color_named[i] << endl;
								//target_color = color_named[i];
								ball_contrast += 1;
							}
						}
						if (ball_contrast == find_big_color) // если цвет целевого обьекта контрастен ко всем цветам фона
						{
							cout << "Target_color: " << color_named[i] << endl;
							target_color = color_named[i];
							find_target_color = true;
						}
						else { ball_contrast = 0; }
					}
					// контрастен ли цвет с наиболее представленым цветом в кадре?
					else
					{
						if (contrast_color(color_named[i], big_color[0]) == 1)
						{
							cout << "Target_color: " << color_named[i] << endl;
							target_color = color_named[i];
							find_target_color = true;
						}
					}
				}
				if (find_target_color == true) // Если найден цвет целевого обьекта
				{
					// Анализируем обьекты в кадре
					frame = Processing_frame(frame, HSV_Frame, target_color, color_named[9]);
					break;
				}
			}

			sec = 0;
			find_big_color = 0;
			ball_contrast = 0;
			find_target_color = false;
			firstRead = true;
		}
		// Нахождения контура по маске и рисование его на оригинальном видеопотоке
		if (draw_HSV == 1)
		{
			// Контур белого цвета
			findContours(mask_white, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(255, 255, 255), 2);
			fillPoly(frame, contours, Scalar(255, 255, 255)); // Закрашивание области внутри контура
			// Контур черного цвета
			findContours(mask_white, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 0, 0), 2);
			fillPoly(frame, contours, Scalar(0, 0, 0)); // Закрашивание области внутри контура
			// Контур красного_1 цвета
			findContours(mask_red_1, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 0, 255), 2);
			fillPoly(frame, contours, Scalar(0, 0, 255)); // Закрашивание области внутри контура
			// Контур оранжевого цвета
			findContours(mask_orange, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 165, 255), 2);
			fillPoly(frame, contours, Scalar(0, 165, 255)); // Закрашивание области внутри контура
			// Контур желтого цвета
			findContours(mask_yellow, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 255, 255), 2);
			fillPoly(frame, contours, Scalar(0, 255, 255)); // Закрашивание области внутри контура
			// Контур зеленого цвета
			findContours(mask_green, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 255, 0), 2);
			fillPoly(frame, contours, Scalar(0, 255, 0)); // Закрашивание области внутри контура
			// Контур голубого цвета
			findContours(mask_aqua, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(255, 170, 66), 2);
			fillPoly(frame, contours, Scalar(255, 170, 66)); // Закрашивание области внутри контура
			// Контур синего цвета
			findContours(mask_blue, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(255, 0, 0), 2);
			fillPoly(frame, contours, Scalar(255, 0, 0)); // Закрашивание области внутри контура
			// Контур фиолетового цвета
			findContours(mask_purple, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(255, 0, 139), 2);
			fillPoly(frame, contours, Scalar(255, 0, 139)); // Закрашивание области внутри контура
			// Контур розового цвета
			findContours(mask_pink, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(203, 192, 255), 2);
			fillPoly(frame, contours, Scalar(203, 192, 255)); // Закрашивание области внутри контура
			// Контур красного_2 цвета
			findContours(mask_red_2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
			drawContours(frame, contours, -1, Scalar(0, 0, 255), 2);
			fillPoly(frame, contours, Scalar(0, 0, 255)); // Закрашивание области внутри контура
		}

		//imshow(window_name, detected_object);
		imshow(window_name, frame);
		//imshow("mask", frame);

		// Вывод в консоль фпс паботы программы
		//fps = cap.get(CAP_PROP_FPS);
		//cout << "Frames per seconds : " << fps << endl;

		if (waitKey(1) == 27) // Wait for 'esc' key press to exit
		{
			break;
		}
	}
	return 0;
}