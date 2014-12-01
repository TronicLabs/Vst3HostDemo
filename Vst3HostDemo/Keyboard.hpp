#include <map>

#include <boost/function.hpp>
#include <boost/optional.hpp>

#include <balor/gui/all.hpp>
#include "./namespace.hpp"

namespace hwm {

class Keyboard
{
	typedef boost::function<void(size_t note_number, bool pushed)> note_handler_t;

private:
	gui::Panel		wnd_;
	gpx::Font		font_key_name_;
	gpx::Bitmap		bitmap_;
	gpx::Graphics	gpx_;
	gui::Timer		timer_;

	boost::optional<size_t> mouse_note_on_;

	int					softkey_base_;
	std::vector<bool>	softkey_note_on_;
	note_handler_t		note_handler_;
	int					note0_pos_;
	int					oct_down_pressed_;
	int					oct_up_pressed_;

	static
	gpx::Color GetWhiteKeyColor();
	static
	gpx::Color GetBlackKeyColor();
	static
	gpx::Color GetKeyFrameColor();
	static
	gpx::Color GetSelectedWhiteKeyColor();
	static
	gpx::Color GetSelectedBlackKeyColor();
public:
	Keyboard();

	Keyboard(gui::Control &parent, int x, int y, int width, int height);

public:
	//! ���Ղ������ꂽ�藣���ꂽ�肵�����ɌĂ΂��
	//! �R�[���o�b�N��ݒ肷��
	void SetNoteHandler(note_handler_t handler);

private:
	void OnPaint(gui::Panel::Paint &e);

	boost::optional<size_t> 
		GetNoteNumber(balor::Point const &pt) const;

	void OnMouseDown(gui::Panel::MouseDown &e);

	void OnMouseMove(gui::Panel::MouseMove &e);

	void OnMouseUp(gui::Panel::MouseUp &e);

	boost::optional<int> shift_from_;
	int stored_note0_pos_;

	void BeginKeyboardViewShift(int x);

	void EndKeyboardViewShift();

	void ShiftKeyboardView(int x);

	static
	std::map<gui::Key, int>
		GenerateKeyMap();

	std::map<gui::Key, int> const &
		GetKeyMap() const;

	//! ���̃E�B���h�E�̃^�C�}�[����Ăяo�����
	//! �L�[�{�[�h�̏�Ԃ��`�F�b�N���āA�m�[�g�M���̑��M��A
	//! �I�N�^�[�u�ݒ�̕ύX���s�����肷��B
	void CheckKeyState();

private:
	bool IsKeyboardViewShiftStarted() const;
};

} // ::hwm