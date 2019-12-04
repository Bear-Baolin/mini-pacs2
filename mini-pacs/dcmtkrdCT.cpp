#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmdata/dcpxitem.h"
#include "dcmtk/dcmimage/diregist.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "opencv-build/"
#include <iostream>



using namespace std;

void main()
{
	string file_path = "E:\\000001.dcm";

	DcmFileFormat fileformat;
	OFCondition oc = fileformat.loadFile(file_path.c_str());
	if (!oc.good())//判断DCM文件是否读取成功
	{
		cout << "file load error" << endl;
		return;
	}
	DcmDataset* dataset = fileformat.getDataset();//得到DICOM的数据集，所有的数据都存储在数据集中
	E_TransferSyntax xfer = dataset->getOriginalXfer();//得到传输句法

	OFString patientname;
	dataset->findAndGetOFString(DCM_PatientName, patientname);
	cout << "patientName:" << patientname << endl;

	unsigned short bit_count(0);
	dataset->findAndGetUint16(DCM_BitsStored, bit_count);//获取像素的位数
	cout << "bit_count:" << bit_count << endl;

	OFString isRGB;
	dataset->findAndGetOFString(DCM_PhotometricInterpretation, isRGB);//DCM图片的图像模式
	cout << "isrgb:" << isRGB << endl;

	unsigned short img_bit(0);
	dataset->findAndGetUint16(DCM_SamplesPerPixel, img_bit);//单个像素占多少帧
	cout << "img_bits:" << img_bit << endl;

	unsigned short m_width;
	unsigned short m_height; //获取图像的窗宽和窗高
	dataset->findAndGetUint16(DCM_Rows, m_height);
	dataset->findAndGetUint16(DCM_Columns, m_width);
	cout << "width:" << m_width << endl;
	cout << "height" << m_height << endl;

	unsigned short center, width;//获取源图像中的窗位和窗宽
	dataset->findAndGetUint16(DCM_WindowCenter, center);
	dataset->findAndGetUint16(DCM_WindowWidth, width);

	DcmElement* element = NULL;//读取dcm中的像素值
	OFCondition result = dataset->findAndGetElement(DCM_PixelData, element);
	if (result.bad() || element == NULL)
	{
		return;
	}
	unsigned short* pixData;
	result = element->getUint16Array(pixData);

}


