// kX Driver / kX Driver Interface / kX Driver Effects Library
// Copyright (c) Eugene Gavrilov, Soeren Bovbjerg 2001-2005.
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

declare_effect_source(Phat_EQ_Stereo);

// Number of plugin parameters
#define Phat_EQ_Stereo_PARAMS_COUNT	4

// Plugin definition
class iPhat_EQ_StereoPlugin : public iKXPlugin
{
public:
	// members of iKXPlugin
	virtual int request_microcode();
	virtual const char *get_plugin_description(int id) { plugin_description(Phat_EQ_Stereo); };

	virtual iKXPluginGUI *create_cp(kDialog *parent, kFile *);
	virtual int get_user_interface();

	virtual int get_param_count(void) {return Phat_EQ_Stereo_PARAMS_COUNT;}
	virtual int describe_param(int ndx, kx_fxparam_descr *descr);	
	virtual int set_defaults();
	virtual int set_param(int ndx, kxparam_t value);
	virtual int get_param(int ndx, kxparam_t *value);
	virtual int set_all_params(kxparam_t* values);

	kxparam_t _params[Phat_EQ_Stereo_PARAMS_COUNT]; // place to store parameters inside the plugin
};

// Plugin GUI definition
class iPhat_EQ_StereoPluginDlg : public CKXPluginGUI
{
public:
	iPhat_EQ_StereoPlugin *plugin;

	// constructor:
	iPhat_EQ_StereoPluginDlg(iPhat_EQ_StereoPlugin *plg, kDialog *parent_, kFile *mf_):CKXPluginGUI(parent_, mf_) {plugin = plg;};

	virtual void init();
	virtual iKXPlugin *get_plugin() { return plugin; };

	// declare GUI Elements

	// Controls
	kFader freq,band,gain,type;

	// for updating UI from plugin
	virtual void sync(int what=EVERYPM_ID);

};
