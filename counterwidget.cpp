#include <QHBoxLayout>
#include <QGridLayout>
#include "counterwidget.h"
#include "config.h"

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this), m_number(0)
{
    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);


    // QLCDNumber zur Anzeige des Zaehlerstandes dezimal:
    m_LCD = new QLCDNumber(3);
    layout->addWidget(m_LCD);
    m_LCD->display(m_number);

    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

// Zaehlerstand im Widget und dual ueber LEDs anzeigen:
void CounterWidget::updateCounter()
{
    if(m_number > 15) m_number = 0;
    if(m_number < 0) m_number = 15;
    if(m_gpio.isActivated(BUTTONS[2]) )
    {
        m_number = (m_number+ 1);
    }
    if(m_gpio.isActivated(BUTTONS[0]))
    {
        m_number = (m_number - 1) ;
    }
    if(m_gpio.isActivated(BUTTONS[1]) )
    {
        m_number = 0;
    }


    m_LCD->display(m_number);
    updLED();
}

void CounterWidget::updLED()
{
    for(int i = 0; i < 4; i++)
        m_gpio.set(LEDS[i], (m_number >> i));
}
