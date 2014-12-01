#pragma once

#include <boost/function.hpp>
#include <balor/gui/all.hpp>

#include "./Keyboard.hpp"
#include "./ControlPanel.hpp"
#include "EditorFrame.hpp"

namespace hwm {

class MainPanel
{
	typedef boost::function<void(balor::String const &module_file_path)> drop_handler_t;
	typedef boost::function<void(size_t note_number, bool note_on)> note_handler_t;

	typedef ControlPanel::program_select_handler_t		program_select_handler_t;
	typedef ControlPanel::plugin_select_handler_t		plugin_select_handler_t;
	typedef ControlPanel::volume_change_handler_t		volume_change_handler_t;
	typedef ControlPanel::peak_level_query_handler_t	peak_level_query_handler_t;
	typedef ControlPanel::IPluginInfo					IPluginInfo;

private:
	gui::Frame					frame_;
	gui::Panel					panel_;
	Keyboard					keyboard_;
	ControlPanel				control_panel_;
	EditorFrame					editor_;
	gui::DragDrop::Target		dnd_target_;

	drop_handler_t drop_handler_;

public:
	MainPanel(balor::String title, int width, int height);
	~MainPanel();

	//! �v���O�C�����h���b�O&�h���b�v�������ɌĂ΂��n���h����ݒ�
	void SetDropHandler(drop_handler_t handler);

	//! �v���O�����i�p�����[�^�̃v���Z�b�g�j���I�����ꂽ���ɌĂ΂��n���h����ݒ�
	void SetProgramSelectHandler(program_select_handler_t handler);

	//! �t�@�C���_�C�A���O����v���O�C�����I�����ꂽ���ɌĂ΂��n���h����ݒ�
	void SetPluginSelectHandler(plugin_select_handler_t handler);

	//! �{�����[���t�F�[�_�[�����삳�ꂽ���ɌĂ΂��n���h����ݒ�
	void SetVolumeChangeHandler(volume_change_handler_t handler);

	//! ���ʂ̖₢���킹�v�����������ɌĂ΂��n���h����ݒ�
	void SetQueryLevelHandler(peak_level_query_handler_t handler);

	//! ���Ղ�������ăm�[�g��񂪑��M���ꂽ���ɌĂ΂��n���h����ݒ�
	void SetNoteHandler(note_handler_t handler);

	void SetNumChannels(size_t channels);

	void AssignPluginToEditorFrame(
			balor::String title,
			boost::function<Steinberg::ViewRect(HWND wnd, IPlugFrame *frame)> assignment_function );

	void DeassignPluginFromEditorFrame(boost::function<void()> deassignment_function);

	void SetPluginInfo(IPluginInfo const &info);
	void ClearPluginInfo();

	//! ���b�Z�[�W���[�v���J�n
	void Run();

	gui::Frame * GetMainFrame();
};

}