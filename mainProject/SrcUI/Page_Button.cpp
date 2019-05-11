#include "Page_Button.h"

PageButton::PageButton(QString pic_name, QWidget *parent)
	:QToolButton(parent)
{
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(13, 13, 13));
	setPalette(text_palette);

	QFont &text_font = const_cast<QFont &>(font());
    text_font.setWeight(QFont::Normal);
	int iSize = text_font.pointSize();
	text_font.setPointSize(iSize + 1);
	iSize = text_font.pointSize();

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(pixmap.size());

	setFixedSize(pixmap.width()+25, pixmap.height()+25);
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
}

PageButton::~PageButton()
{

}

void PageButton::enterEvent(QEvent *)
{
	mouse_over = true;
}

void PageButton::leaveEvent(QEvent *)
{
	mouse_over = false;
}

void PageButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

void PageButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void PageButton::paintEvent(QPaintEvent *event)
{
	if(mouse_over)
	{
//		painterInfo(0, 80, 200);
		painterInfo(50, 120, 150);
	}
	else
	{
		if(mouse_press)
		{
			painterInfo(50, 180, 220);
		}
	}

	QToolButton::paintEvent(event);
}


//	linear.setColorAt(0, QColor(0xEE, 0x82, 0xEE, top_color));
//	linear.setColorAt(0.5, QColor(0xEE, 0x82, 0xEE, middle_color));
//	linear.setColorAt(1, QColor(0xEE, 0x82, 0xEE, bottom_color));
void PageButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(0xEA, 0xEA, 0xEA, top_color));
	linear.setColorAt(0.25, QColor(0xEA, 0xEA, 0xEA, middle_color));
	linear.setColorAt(0.50, QColor(0xEA, 0xEA, 0xEA, bottom_color));
	linear.setColorAt(0.75, QColor(0xEA, 0xEA, 0xEA, middle_color));
	linear.setColorAt(1., QColor(0xEA, 0xEA, 0xEA, top_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
