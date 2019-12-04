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
	if (!oc.good())//�ж�DCM�ļ��Ƿ��ȡ�ɹ�
	{
		cout << "file load error" << endl;
		return;
	}
	DcmDataset* dataset = fileformat.getDataset();//�õ�DICOM�����ݼ������е����ݶ��洢�����ݼ���
	E_TransferSyntax xfer = dataset->getOriginalXfer();//�õ�����䷨

	OFString patientname;
	dataset->findAndGetOFString(DCM_PatientName, patientname);
	cout << "patientName:" << patientname << endl;

	unsigned short bit_count(0);
	dataset->findAndGetUint16(DCM_BitsStored, bit_count);//��ȡ���ص�λ��
	cout << "bit_count:" << bit_count << endl;

	OFString isRGB;
	dataset->findAndGetOFString(DCM_PhotometricInterpretation, isRGB);//DCMͼƬ��ͼ��ģʽ
	cout << "isrgb:" << isRGB << endl;

	unsigned short img_bit(0);
	dataset->findAndGetUint16(DCM_SamplesPerPixel, img_bit);//��������ռ����֡
	cout << "img_bits:" << img_bit << endl;

	unsigned short m_width;
	unsigned short m_height; //��ȡͼ��Ĵ���ʹ���
	dataset->findAndGetUint16(DCM_Rows, m_height);
	dataset->findAndGetUint16(DCM_Columns, m_width);
	cout << "width:" << m_width << endl;
	cout << "height" << m_height << endl;

	unsigned short center, width;//��ȡԴͼ���еĴ�λ�ʹ���
	dataset->findAndGetUint16(DCM_WindowCenter, center);
	dataset->findAndGetUint16(DCM_WindowWidth, width);

	DcmElement* element = NULL;//��ȡdcm�е�����ֵ
	OFCondition result = dataset->findAndGetElement(DCM_PixelData, element);
	if (result.bad() || element == NULL)
	{
		return;
	}
	unsigned short* pixData;
	result = element->getUint16Array(pixData);

}


