// 五子棋Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "五子棋.h"
#include "五子棋Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int board[14][14];   //棋盘数组
BOOL ptable[14][14][480]; //人的所有可能的赢法数组
BOOL ctable[14][14]
[480]; //计算机所有可能的赢法数组
int ccgrade[14][14] ={0}; //计算机的权值数组
int ppgrade[14][14] ={0}; //人的权值数组
int cgrade,pgrade;
int win[2][480]; // win[0][480]表示人在480中赢法的值，
                 //当他的一个值是5时表示他已经赢了
                 // win[1][480]表示计算机在480中赢法的值，
                 //当他的一个值是5时表示他已经赢了
int pcount,ccount;
BOOL player,computer,start = true ,over , pwin, cwin, tie; //这里都时一些标记 其中tie表示是否平局的标记
int i,j,k,m,n,count;
int mat,nat,mde,nde;
char str[14];
// void dostep();

/////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support//函数是进行数据交换的
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
 //   SetTimer(1,2000,NULL);
	for(i = 0 ; i<14; i++)
	  for(j= 0 ;j <14 ;j++)
		  board[i][j] = 2; // 初始化棋盘数组
	  for(i = 0 ; i <14 ; i++) //对14列进行隔行扫描，
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j+k][i][count] = true;  
			  ctable[j+k][i][count] = true;
		  }


		  count ++;
	  }
	 for(i = 0 ; i <14 ; i++) //对14行进行隔行扫描
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[i][j+k][count] = true;
			  ctable[i][j+k][count] = true;
		  }


		  count ++;
	  }
	
	for(i = 0 ; i <10; i++) //对交叉的情况－东南－西北走向－ 进行扫描
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j+k][i+k][count] = true;
			  ctable[j+k][i+k][count] = true;
		  }


		  count ++;
	  }
	
for(i = 0 ; i <10 ; i++) //对交叉的情况－东北－西南走向－ 进行扫描
	  for(j=13 ; j >= 4 ; j--)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j-k][i+k][count] = true;
			  ctable[j-k][i+k][count] = true;
		  }


		  count ++;
	  }	
	
	
	//说明 在这里到底是人先下还是计算机先下，可以自己设定
	player = true;

	count = 0 ;
	m_board = new CBitmap;
	m_white = new CBitmap;
	m_black = new CBitmap;
    m_temp = new CBitmap;
	m_red = new CBitmap;
   // m_bitmap4 = new CBitmap;
    //以下实现的是加载位图的功能。
	
	m_board->m_hObject  = (HBITMAP)::LoadImage (NULL,"checkerboard.bmp",IMAGE_BITMAP,320,320,LR_LOADFROMFILE);
	m_white->m_hObject = (HBITMAP)::LoadImage (NULL,"bai.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);
    m_black->m_hObject = (HBITMAP)::LoadImage (NULL,"hei.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);
    m_temp->m_hObject = (HBITMAP)::LoadImage (NULL,"mask1.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);
   	m_red->m_hObject = (HBITMAP)::LoadImage (NULL,"dred.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);
	
	// m_bitmap4->m_hObject = (HBITMAP)::LoadImage (NULL,"temp.bmp",IMAGE_BITMAP,20,20,LR_LOADFROMFILE);

	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_board.m_hObject = (HBI
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_restart, Onrestart)
	ON_BN_CLICKED(IDC_start, Onstart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
  //以下代码实现的是绘制位图的功能
	CDC thmem3 ;
	 CClientDC dc(this);
	 thmem3.CreateCompatibleDC(&dc);
	 thmem3.SelectObject(m_board);
	 dc.BitBlt(0,0,320,320,&thmem3,0,0,SRCCOPY); 
	 	
	CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//函数实现了响应点击鼠标左键的功能
void CMyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	
	
	
	 int m ,n;
	 CDC thmem1 ;
	 CClientDC dc(this);
	 thmem1.CreateCompatibleDC(&dc);
//	 dc.TextOut (12,23,"fhdtdfhad f ");
   int curx = point.y;
   int cury = point.x;
   m =int((curx-15)/20);
   n = int((cury-25)/20);
  
if(!over)
  if(player)
  {
		    
     if(curx>=15 && cury >=25 && curx <= 315 && cury <=325 && board[m][n] ==2)
	 {
		  board[m][n] = 0 ; //set for the player //把board[m][n]数组置为0
		  pcount ++;
		  if((ccount == 98)&&(pcount == 98))  //当人跟计算机都各自下了98个子还没有分出输赢的话，那就算平局
		  {
			  tie = true;
			  over = true;
		  }
                                  //对480种可能的情况都要扫描
		  for(i = 0 ; i<480; i++) //对于鼠标所点的那个点转化成棋盘数组中某个具体的值后应该对跟这个点相关的赢法都加一
		  {
			   if(ptable[m][n][i] && win[0][i] != 8) //win[0][i] == 8 只是程序设计时所做的一个标记，表示这个点已经被计算机算走了，同理win[1][i] == 8 反一下
				   win[0][i]++;
			   if(ctable[m][n][i])
			   {
				   ctable[m][n][i] = false;
				   win[1][i] = 8;
			   }
		  }
		  player = false;   //turn to the computer first;
		  computer = true;
	 }
 }


	
	CDialog::OnLButtonDown(nFlags, point); //基类的响应鼠标左键函数
	dostep();  // 函数的功能时开始在界面上演示走棋的效果
	return;
}


void CMyDlg::Computer ()
{
	//以下函数时设置权值的功能，为计算机选择最佳的落子点做好准备

	for(i = 0 ; i<= 13 ; i++)
		for( j= 0 ; j <=13 ;j++)
		{
			ppgrade[i][j] = 0 ;
			if(board[i][j] ==2)
				for(k=0 ; k <480 ; k++)
					if(ptable[i][j][k])
					{
						 switch(win[0][k])
						 {
						 case 1:
							 ppgrade[i][j] +=5;
						      break;

						 case 2:
							 ppgrade[i][j] +=50;
						       break;

						 case 3:
							 ppgrade[i][j] +=100;
						      break;

						 case 4:
							 ppgrade[i][j] +=400;
							 break;

						 }
					}
		}


		for(i = 0 ; i<= 13; i++)
			for(j=0 ; j<=13;j++)
			{
				ccgrade[i][j] = 0 ;
				if( board[i][j]==2)
				for(k=0 ; k <480 ; k++)
					if(ctable[i][j][k])
					{
						 switch(win[1][k])
						 {
						 case 1:
							 ccgrade[i][j] +=5;
						      break;

						 case 2:
							 ccgrade[i][j] +=50;
						       break;

						 case 3:
							 ccgrade[i][j] +=100;
						      break;

						 case 4:
							 ccgrade[i][j] +=400;
							 break;

						 }
					}
}

if(start)
{
  //选择计算机开始落子的位子
	if( board[7][7] == 2)
  {
	  m = 7;
	  n = 7;
  }
  else{
	  m = 8 ;
	  n = 8;
  }
  start = false;
}
else
{
	for(i= 0 ; i<14 ; i++)
		for( j = 0 ; j<14;j++)
			if(board[i][j] ==2)
			{
				//以下是选择计算机权值最大的点，和当时的权值
				if(ccgrade[i][j] >= cgrade)
				{
					cgrade = ccgrade[i][j];
					mat = i;
					nat = j;
				}
				//以下是选择个人权值最大的点，和当时的权值
				if(ppgrade[i][j] >= pgrade)
				{
					pgrade = ppgrade[i][j];
					mde = i;
					nde = j;
				}
			}
		   //看计算机最大的值跟个人最大的值那个大，如果计算机大的话，那就进攻
			if(cgrade >= pgrade) //for attack;
			{
				m = mat;
				n = nat;
			}

			//否则的话那就防守
			else
			{
				m = mde;
				n = nde;
			}
}
cgrade = 0 ;
pgrade = 0 ;
board[m][n] = 1; //paste the computer chess in this position;
ccount ++;
if((ccount ==98 )&&(pcount ==98))
{
	  tie = true;
	  over = true;
}

//跟人下好一个棋后所做的处理是一致的
for( i= 0 ; i<480 ; i++)
{
	if(ctable[m][n][i]&&win[1][i] !=8 ) 
		win[1][i]++;
    	if(ptable[m][n][i])
		{
	 	  ptable[m][n][i] = false;
		  win[0][i] = 8;
		}
}
	player = true; //call the player to start
	computer = false;
}







void CMyDlg::dostep() 
{
	// TODO: Add your message handler code here and/or call default

	 CDC thmem2 ; //thmem3
	 CClientDC dc(this);
	 thmem2.CreateCompatibleDC(&dc);
    // thmem3.CreateCompatibleDC(&dc);
	 
   int ii,jj,kk;
	
	if(!over)
	{
		if(computer)
			Computer();
		for(i=0 ; i<=1 ;i++)
			for(j=0 ; j<480 ; j++)
			{
			if(win[i][j] == 5)// 看是否5子连书了，是的话，用红色的棋子显示以下，然后打出一句话
					if(i==0)
					{ //人赢了
						pwin = true;
						over = true;
						for(ii= 0 ; ii <=13 ;ii++)
						   for(jj = 0 ; jj <=13 ;jj++)
                           if(ptable[ii][jj][j] == true)
						   { 
							   
							   
						     thmem2.SelectObject(m_temp);
						      dc.BitBlt(jj*20+25,ii*20+15,20,20,&thmem2,0,0,MERGEPAINT);
						     
							  thmem2.SelectObject(m_red);
						     dc.BitBlt(jj*20+25,ii*20+15,20,20,&thmem2,0,0,SRCAND);
					
						   }
					  //	MessageBox("恭喜你，你赢了");
						   
						   for(ii= 0 ; ii <10000 ; ii++)
						for(jj = 0 ; jj <30000 ; jj++);
						   
						   break;

					}
					else
					{
					  //计算机赢了   
					 cwin  = true;
					   over = true;
					   for(ii= 0 ; ii <=13 ;ii++)
						   for(jj = 0 ; jj <=13 ;jj++)
                           if(ctable[ii][jj][j] == true)
						   { 
							   
							   
							 thmem2.SelectObject (m_temp);
						      dc.BitBlt(jj*20+25,ii*20+15,20,20,&thmem2,0,0,MERGEPAINT);
						     
							  thmem2.SelectObject (m_red);
						      dc.BitBlt(jj*20+25,ii*20+15,20,20,&thmem2,0,0,SRCAND);
					
					} 
						
						   //	MessageBox("你输了  ，要继续请从新开始!");
					   for(ii= 0 ; ii <10000 ; ii++)
						 for(jj = 0 ; jj <15000 ; jj++);
						   
						   break;

					}

               if(over)
				   break;
			}
	}
		
//没有五子连书的情况的下，那就简单的把子显示一下了

	     for(i = 0 ; i <=13 ; i++)
		    	for( j = 0 ; j<= 13 ; j++)
				{
				   if(board[i][j]==0)
				   {   
					thmem2.SelectObject (m_temp);
				    dc.BitBlt(j*20+25,i*20+15,20,20,&thmem2,0,0,MERGEPAINT);
					thmem2.SelectObject (m_black);
					dc.BitBlt (j*20+25,i*20+15,20,20,&thmem2,0,0,SRCAND);
				//	m_byColour = white ;
			    //	UpdataData(FALSE);
					for(ii= 0 ; ii <1000 ; ii++)
						for(jj = 0 ; jj <1000 ; jj++);
				//	dc.TextOut (50,400,"  。。。。。。。。。。该你下了。。。。。。。。。。。");
				}
				if(board[i][j] == 1)
				{
                      
					thmem2.SelectObject (m_temp);
				    dc.BitBlt(j*20+25,i*20+15,20,20,&thmem2,0,0,MERGEPAINT);
					thmem2.SelectObject (m_white);
					dc.BitBlt (j*20+25,i*20+15,20,20,&thmem2,0,0,SRCAND);
					m_byColour = black;
				//	UpdateData();
					for(ii= 0 ; ii <1000 ; ii++)
						for(jj = 0 ; jj <1000 ; jj++);
											
				}


			}
		//人赢，打出这句话
				if(pwin)
			{     MessageBox("看来你还挺聪明的嘛，继续努力吧");
			
				// dc.TextOut (50,360,"你赢了，按下restart键，重新开始!");
			 //  KillTimer(1);
			}
		
			// 计算机赢，打出这句话
				if(cwin)
			{    MessageBox("看来你是水平还比较差，不服再来!!!!");

				//dc.TextOut (50,360,"你输了，按下restart键，重新开始!");
			//  KillTimer(1);
			}

	
	
	
	
	
//	CDialog::OnTimer(nIDEvent);
}


//自己改变光标的显示
BOOL CMyDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint point, pt;
	::GetCursorPos(&point);
   	ScreenToClient(&point);
	if (point.y>=15 && point.x>=25 && point.y <= 315 && point.x <=325&& !over)
	{	
		::SetCursor(AfxGetApp()->LoadCursor(m_byColour ? IDC_BLACK_CURSOR:IDC_WHITE_CURSOR));
		return TRUE;
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


/*BOOL CMyDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}*/




//当点击重新开始是的所作的工作

void CMyDlg::Onrestart() 
{
	// TODO: Add your control notification handler code here
		for(i = 0 ; i<14; i++)
	  for(j= 0 ;j <14 ;j++)
		  board[i][j] = 2;
	  for(i = 0 ; i <14 ; i++)
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j+k][i][count] = true;
			  ctable[j+k][i][count] = true;
		  }


		  count ++;
	  }
	 for(i = 0 ; i <14 ; i++)
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[i][j+k][count] = true;
			  ctable[i][j+k][count] = true;
		  }


		  count ++;
	  }
	
	for(i = 0 ; i <10; i++)
	  for(j=0 ; j <10 ; j++)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j+k][i+k][count] = true;
			  ctable[j+k][i+k][count] = true;
		  }


		  count ++;
	  }
	
for(i = 0 ; i <10 ; i++)
	  for(j=13 ; j >= 4 ; j--)
	  {
		  for( k = 0 ; k <5 ;k++)
		  {
			  ptable[j-k][i+k][count] = true;
			  ctable[j-k][i+k][count] = true;
		  }


		  count ++;
	  }	
	
	
	//说明 在这里到底是人先下还是计算机先下，可以自己设定
pwin = false;
cwin = false;

player = true;
over = false;
computer = false;
 cgrade = 0 ;
 pgrade = 0 ;
 for(i = 0 ;i <14; i++)
	 for(j = 0 ; j <14 ; j++)
	 {  ppgrade[i][j] = 0 ;
	    ccgrade[i][j] = 0 ;
	 }

for(i=0 ; i <=1 ;i++)
  for(j=0 ; j<480 ; j++)
    win[i][j] = 0 ;
	 

 count = 0 ;
 CDC thmem2 ; //thmem3
 CClientDC dc(this);
 thmem2.CreateCompatibleDC(&dc);
 thmem2.SelectObject(m_board);
 dc.BitBlt (0,0,320,320,&thmem2,0,0,SRCCOPY);

Invalidate(false);
   



	
}

//点击开始时弹出一个对话框，内容为你让你执黑先下
void CMyDlg::Onstart() 
{

	MessageBox("让 你 执 黑 先 下 ");

	m_byColour = black;

	
	
	// TODO: Add your control notification handler code here
	
}
