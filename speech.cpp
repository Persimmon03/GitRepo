
#include<iostream>
#include<sapi.h>
#include<sphelper.h>
#include<Windows.h>
//#include<atlbase.h>
//#include<atlhost.h>



using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	HRESULT hr;
	if(FAILED(::CoInitialize(NULL)))
		return false;
		
    /*ISpVoice *pVoice = nullptr;

#ifdef CHN
	WCHAR ChineseTokenId[] = L"HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Speech\\Voices\\Tokens\\MSSimplifiedChineseVoice";
	ISpObjectToken *pChineseToken;
	SpGetTokenFromId(ChineseTokenId, &pChineseToken);
#endif
	
	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (VOID **)&pVoice);

	if(SUCCEEDED(hr))
	{
#ifdef CHN
		pVoice->SetVoice(pChineseToken);
#endif
		hr = pVoice->Speak(L"apple", 0, NULL);
		pVoice->Release();
		pVoice = nullptr;
	}*/


	CComPtr<ISpRecognizer> m_cpRecognizer;
	CComPtr<ISpRecoContext> m_cRecoCtxt;
	CComPtr<ISpRecoGrammar> m_cpCmdGrammer;
	CComPtr<ISpAudio> m_cpAudio;

	if(SUCCEEDED(hr = m_cpRecognizer.CoCreateInstance(CLSID_SpSharedRecognizer)) &&
	   SUCCEEDED(hr = m_cpRecognizer->CreateRecoContext(&m_cRecoCtxt)) &&
	   SUCCEEDED(hr = m_cRecoCtxt->SetNotifyWin32Event()) &&
	   SUCCEEDED(hr = m_cRecoCtxt->SetInterest(SPFEI(SPEI_RECOGNITION), SPFEI(SPEI_RECOGNITION))) &&
	   SUCCEEDED(hr = m_cRecoCtxt->CreateGrammar(0,&m_cpCmdGrammer)) &&
	   SUCCEEDED(hr = m_cpCmdGrammer->LoadCmdFromFile(L"CmdCtrl.xml",SPLO_DYNAMIC)) &&
	   SUCCEEDED(hr = m_cpCmdGrammer->SetRuleState(NULL,NULL,SPRS_ACTIVE)))
	{
		USES_CONVERSION;
		CSpEvent event;
		hr = S_OK;

		BSTR SRout;
		cout<<"Please start speaking:"<<endl;
		while(1)
		{
			while(event.GetFrom(m_cRecoCtxt) == S_OK)
			{
				switch(event.eEventId)
				{
					case SPEI_RECOGNITION:
					{
						static const WCHAR wszUnrecognized[]= L"Unrecognized";
						CSpDynamicString dstrText;
						if(FAILED(event.RecoResult()->GetText(SP_GETWHOLEPHRASE,SP_GETWHOLEPHRASE,true,&dstrText,NULL)))
						{
							dstrText = wszUnrecognized;
						}
						else
						{
							temp = dstrText.CopyToChar();
							std::string something = temp;
							//cout<<W2A(dstrText)<<endl;
						}
					}
				}
			}
		}
	}
		

	::CoUninitialize();

	return 0;
}

