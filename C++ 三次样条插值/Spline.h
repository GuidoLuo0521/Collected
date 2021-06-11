#ifndef CUBICSPLINE
#define CUBICSPLINE

#include <vector>
#include <cmath>


//�Զ���ĵ�����
struct MYPOINT
{
	double x, y ,z;
	
};

//�������ɲ��������β�ֵ��������
class Spline {

public:

	//���ɵ����ߵ�
	std::vector<double> spline_u;
	
	MYPOINT begin_k1;//��㵼ʸ
	MYPOINT end_k1;//�յ㵼ʸ
	int interval;//�������ߵ������
public:
	//�յĹ��캯����������Ժ����setVertex�����ò�ֵ��
	Spline(){}
	//���ò�ֵ��
	void setVertex(std::vector<MYPOINT> point, int interval_ );

	//���ߵ㵼ʸ
	std::vector<MYPOINT> daoshi;
	//��õ�
	std::vector<MYPOINT> get_point();

	std::vector<MYPOINT> spline_create(int i = 2);
	
private:
	std::vector<MYPOINT> m_aVertex;//��ֵ��,��ĿΪnum
	std::vector<double> distance;//�ҳ�(num-1)
	std::vector<double> distance_sum_n;
	std::vector<double> canshu_u;//��ֵ��Ĳ���ֵ(num)
	std::vector<double> delta;//delta(num-1)
	std::vector<MYPOINT> all_point;//���ߵ�

	std::vector<std::vector<double>>  matrix_m;
	std::vector<std::vector<double>>  matrix_right;

	//��ֵ�㵼ʸ
	std::vector<std::vector<double>>  daoshi_vec;
	std::vector<MYPOINT> _p;

	std::vector<double> m_Cx;//ÿ����ֵ��ĵ�ʸ��x
	std::vector<double> m_Cy;//ÿ����ֵ��ĵ�ʸ��y
	std::vector<double> m_Cz;//ÿ����ֵ��ĵ�ʸ��z

private:
	//�淶�����ҳ�������
	void parameterization();

	void setMatrix(int condition);

	void getDerivative();

	void tridia(int n, int k, std::vector<std::vector<double>>&dia, std::vector<std::vector<double>>&t,
		int iflag);

	void getSplineDerivat(int i, double u, int j, MYPOINT &p);

	void getCubicCuvValue(int i, std::vector<double> &tx, std::vector<double> &ty, std::vector<double> &tz,double u,
		int j, MYPOINT &p);

};

#endif