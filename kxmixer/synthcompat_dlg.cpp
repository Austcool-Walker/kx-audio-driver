// kX Mixer
// Copyright (c) Eugene Gavrilov, 2001-2005.
// All rights reserved

/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */


// inlined

#undef PARAMETERS
#define PARAMETERS  10

// Selection dialog classes
class CSynthSettingsDlg : public kDialog
{
public:
 CSynthSettingsDlg **that;

 CSynthSettingsDlg(iKX *ikx_t_,CSynthSettingsDlg **that_) : kDialog() 
 { that=that_; ikx_t=ikx_t_; ikx_t->get_hw_parameter(KX_HW_SYNTH_COMPATIBILITY,(dword *)&flag); };

 const char *get_class_name() { return "kXSettingsSynthCompat"; };
 iKX *ikx_t;

 kButton b_ok;
 kButton b_cancel;
 kCombo c_synth;

 kStatic label;
 int flag;

 CButton b_list[PARAMETERS];

 virtual void init()
 {
  kDialog::init();

  ::set_font(this,font,"synth_compat");

  set_tool_font(font);

  //SetClassLong(m_hWnd,GCL_STYLE,GetClassLong(m_hWnd,GCL_STYLE)|0x00020000); // CS_DROPSHADOW

  char tmp_str[256];

  unsigned int transp_color=0x0;
  unsigned int alpha=90;
  unsigned int cc_method=0;

  if(mf.get_profile("synth_compat","background",tmp_str,sizeof(tmp_str)))
  {
   tmp_str[0]=0;
  }

  gui_set_background(this,&mf,tmp_str,transp_color,alpha,cc_method,_T("mixer/synth_compat.jpg"));

  set_dragging(gui_get_show_content());

  // label
  if(!mf.get_profile("synth_compat","label",tmp_str,sizeof(tmp_str)))
  {
   dword fg=0,bk=0;
   RECT r; memset(&r,0,sizeof(r));

   sscanf(tmp_str,"%d %d %d %d %x %x",&r.left,&r.top,&r.right,&r.bottom,&fg,&bk);
   label.create((char *)(LPCTSTR)mf.get_profile("synth_compat","label.text"),r.left,r.top,r.right,r.bottom,this,fg,bk);
   label.ShowWindow(SW_SHOW);
   label.SetFont(font);
  }

  SetWindowText(mf.get_profile("lang","settings.synth"));
  
  if(!mf.get_profile("synth_compat","cancel_button",tmp_str,sizeof(tmp_str)))
  {
   gui_create_button(this,&b_cancel,IDCANCEL,tmp_str,mf);
   b_cancel.ShowWindow(SW_SHOW);
  }
  if(!mf.get_profile("synth_compat","ok_button",tmp_str,sizeof(tmp_str)))
  {
   gui_create_button(this,&b_ok,IDOK,tmp_str,mf);
   b_ok.ShowWindow(SW_SHOW);
  }

  int set_x=15,set_y=15;
  int set_wd=120,set_ht=20;
  int set_gap_x=100,set_gap_y=18;
  if(!mf.get_profile("synth_compat","layout",tmp_str,sizeof(tmp_str)))
  {
   sscanf(tmp_str,"%d %d %d %d %d %d",&set_x,&set_y,&set_wd,&set_ht,&set_gap_x,&set_gap_y);
  }

  int i=0;
  for(int x=0;x<3;x++)
  {
   for(int y=0;y<5;y++)
   {
    char tmp[KX_MAX_STRING];
    sprintf(tmp,"settings.synth%d",i+1);
    RECT r;
    r.left=set_x+x*set_wd;
    r.top=set_y+y*set_ht;
    r.right=r.left+set_gap_x;
    r.bottom=r.top+set_gap_y;

    b_list[i].Create(mf.get_profile("lang",tmp),BS_AUTOCHECKBOX,r,this,0x1000+i);
    b_list[i].ShowWindow(TRUE);
    if(flag&(1<<i))
     b_list[i].SetCheck(1);

    if(font.get_font())
     b_list[i].SetFont(font);

    i++;
    if(i==PARAMETERS)
     break;
   }
    if(i==PARAMETERS)
     break;
  }

  kRect rr;
  rr.left=140; rr.top=40; rr.right=200; rr.bottom=60;
  if(!mf.get_profile("synth_compat","bank",tmp_str,sizeof(tmp_str)))
  {
   sscanf(tmp_str,"%d %d %d %d",&rr.left,&rr.top,&rr.right,&rr.bottom);
  }

  c_synth.create(rr,CBS_DROPDOWNLIST /*| CBS_AUTOHSCROLL | WS_VSCROLL*/,2000,this);
  add_tool((char *)(LPCTSTR)mf.get_profile("lang","settings.compat.bank"),&c_synth,2000);
  if(font.get_font())
   c_synth.set_font(font);

  c_synth.add_string("Default (LSB+MSB)");
  c_synth.add_string("LSB");
  c_synth.add_string("MSB");
  c_synth.add_string("LSB & MSB");

  c_synth.set_selection((flag>>10)&0x3);
  c_synth.show();

  CenterWindow();
 };
 afx_msg void OnChange() 
 { 
  flag&=~KX_SYNTH_COMPAT_BANK;
  flag|=c_synth.get_selection()<<10;
 };

 BOOL OnCommand(WPARAM wParam, LPARAM lParam)
 {
  if(wParam>=0x1000 && wParam<=(0x1000+PARAMETERS))
  {
   flag=0;
   for(int i=0;i<PARAMETERS;i++)
    if(b_list[i].GetCheck()==1)
     flag|=(1<<i);
    else
     flag&=~(1<<i);
  }
  return kDialog::OnCommand(wParam,lParam);
 };

 void on_cancel() { PostMessage(WM_DESTROY); };
 void on_ok() { ikx_t->set_hw_parameter(KX_HW_SYNTH_COMPATIBILITY,flag); PostMessage(WM_DESTROY); };
 void on_post_nc_destroy() { if(that && (*that)) *that=0; delete this; };

 DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CSynthSettingsDlg, kDialog)
 ON_CBN_SELCHANGE(2000, OnChange)
END_MESSAGE_MAP()
