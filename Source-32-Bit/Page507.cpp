// Page507.cpp: implementation of the CPage507 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lspc.h"
#include "Page507.h"
#include "MainFrm.h"
#include "LSPCView.h"
#include "LSPCDoc.h"
#include "LSPCMODEL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPage507::CPage507()
{

}

CPage507::CPage507(UINT nID) : CPageAdd(nID)
{

}

CPage507::~CPage507()
{

}

void CPage507::InitGrid()
{
	m_Grid.SetRowCount(1);
	m_Grid.SetColumnCount(14);
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetFixedColumnCount(0);

	CString str[] ={"defid","deluid","jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"}; // column name

	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT;
	Item.row = 0;
	Item.nFormat = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
	
	for (int col = 0; col < m_Grid.GetColumnCount(); col++)
	{ 
		Item.col = col;
		Item.szText = str[col];
		m_Grid.SetItem(&Item);
	}
	m_Grid.AutoSize();
}

BOOL CPage507::UpdateData( BOOL bSaveAndValidate)
{
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	CLSPCView *pView = (CLSPCView *)pMain->m_wndSplitter.GetPane(0,1);
	if(pView == NULL)
		return false;

	CLSPCDoc *pDoc = pView->GetDocument();
	if(pDoc == NULL)
		return false;
	
	int nNum = pDoc->lspc.nlandp*pDoc->lspc.ngroup;

	if(bSaveAndValidate)
	{
		if(pDoc->lspc.maco2fg  != 1 || pDoc->lspc.oxfg != 1)
			return true;

		int nRow = m_Grid.GetRowCount() - 1;
		if(nRow != nNum)
		{
			AfxMessageBox("Card 507: Number of rows should be equal to nlandp*ngroup in Card 507!");
			Log("Card 507: Number of rows should be equal to nlandp*ngroup in Card 507!");
			return false;
		}

		// delete the old one
		if(pDoc->lspc.aco2conc != NULL)
			delete [](pDoc->lspc.aco2conc);

		if (nNum > 0)
			pDoc->lspc.aco2conc = new MONTH_OX[nNum];
		
		for(int i = 0; i < nNum; ++i)
		{
			pDoc->lspc.aco2conc[i].gid      = m_Grid.GetItemInt(i+1,  0);
			pDoc->lspc.aco2conc[i].lid      = m_Grid.GetItemInt(i+1,  1);
			pDoc->lspc.aco2conc[i].fnum[0]  = m_Grid.GetItemFloat(i+1,2);
			pDoc->lspc.aco2conc[i].fnum[1]  = m_Grid.GetItemFloat(i+1,3);
			pDoc->lspc.aco2conc[i].fnum[2]  = m_Grid.GetItemFloat(i+1,4);
			pDoc->lspc.aco2conc[i].fnum[3]  = m_Grid.GetItemFloat(i+1,5);
			pDoc->lspc.aco2conc[i].fnum[4]  = m_Grid.GetItemFloat(i+1,6);
			pDoc->lspc.aco2conc[i].fnum[5]  = m_Grid.GetItemFloat(i+1,7);
			pDoc->lspc.aco2conc[i].fnum[6]  = m_Grid.GetItemFloat(i+1,8);
			pDoc->lspc.aco2conc[i].fnum[7]  = m_Grid.GetItemFloat(i+1,9);
			pDoc->lspc.aco2conc[i].fnum[8]  = m_Grid.GetItemFloat(i+1,10);
			pDoc->lspc.aco2conc[i].fnum[9]  = m_Grid.GetItemFloat(i+1,11);
			pDoc->lspc.aco2conc[i].fnum[10] = m_Grid.GetItemFloat(i+1,12);
			pDoc->lspc.aco2conc[i].fnum[11] = m_Grid.GetItemFloat(i+1,13);
		}
	}
	else
	{
		InitGrid();

		if(pDoc->lspc.aco2conc == NULL)
			return true;

		CSize size = m_Grid.GetTextExtent(" ");
		for(int i =0; i < nNum; ++i)
		{
			m_Grid.InsertRow(_T(""), -1);	
			int nRow = m_Grid.GetRowCount() - 1;
			m_Grid.SetRowHeight(nRow, size.cy);
			m_Grid.SetItemInt(nRow,  0, pDoc->lspc.aco2conc[i].gid);
			m_Grid.SetItemInt(nRow,  1, pDoc->lspc.aco2conc[i].lid);
			m_Grid.SetItemFloat(nRow,2, pDoc->lspc.aco2conc[i].fnum[0]);
			m_Grid.SetItemFloat(nRow,3, pDoc->lspc.aco2conc[i].fnum[1]); 
			m_Grid.SetItemFloat(nRow,4, pDoc->lspc.aco2conc[i].fnum[2]); 
			m_Grid.SetItemFloat(nRow,5, pDoc->lspc.aco2conc[i].fnum[3]);
			m_Grid.SetItemFloat(nRow,6, pDoc->lspc.aco2conc[i].fnum[4]); 
			m_Grid.SetItemFloat(nRow,7, pDoc->lspc.aco2conc[i].fnum[5]); 
			m_Grid.SetItemFloat(nRow,8, pDoc->lspc.aco2conc[i].fnum[6]); 
			m_Grid.SetItemFloat(nRow,9, pDoc->lspc.aco2conc[i].fnum[7]); 
			m_Grid.SetItemFloat(nRow,10,pDoc->lspc.aco2conc[i].fnum[8]); 
			m_Grid.SetItemFloat(nRow,11,pDoc->lspc.aco2conc[i].fnum[9]); 
			m_Grid.SetItemFloat(nRow,12,pDoc->lspc.aco2conc[i].fnum[10]);
			m_Grid.SetItemFloat(nRow,13,pDoc->lspc.aco2conc[i].fnum[11]);
		}
		m_Grid.Invalidate();
		m_Grid.AutoSize();
	}
	return TRUE;
}
