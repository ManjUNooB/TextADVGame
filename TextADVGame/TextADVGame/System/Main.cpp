#include <System/Main.h>
#include <Defines.h>

//�搶�����}�N��
//�悭�킩���
//���邩��ɏ��������s���̃}�N���Ȃ񂾂낤����
//�ǂ������������Ă�̂������ς�
//����������\��
//fn�ɏ������֐���������
//HRESULT�^��hr�ɏ������֐��̏������ʂ�����B
//FAILED�Ȃ烁�b�Z�[�W�{�b�N�X�Ń��b�Z�[�W���o�͂���
//�G���[���o����hr��߂��B
//do while�Ȃ̂ŏ����𖞂����Ă��Ȃ��Ƃ����s����
#define ASSERT_FAILED(fn) do{\
hr = fn; \
if(FAILED(hr)){ \
	MessageBox(nullptr,"Init failed : "#fn, "Error",MB_OK);	\
	return hr; \
}} while(0)

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	//ASSERT_FAILED(InitDx(hWnd, width, height, false)); DirectX������
	//ASSERT_FAILED(InitGeometory());	//�W�I���g��������
	//ASSERT_FAILED(InitInput());	//���͏�����
}