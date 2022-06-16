#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QVBoxLayout>

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    ImageButton() = default;
    ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
public slots:
    void setYellow();
    void setRed();
    void setGreen();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonYellowPixmap;
    QPixmap mButtonRedPixmap;
    QPixmap mButtonGreenPixmap;
};

ImageButton::ImageButton(QWidget *parent)
{
    setParent(parent);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mButtonYellowPixmap = QPixmap("C:\\buttons\\Y.png");
    mButtonRedPixmap = QPixmap("C:\\buttons\\R.png");
    mButtonGreenPixmap = QPixmap("C:\\buttons\\G.png");
    mCurrentButtonPixmap = mButtonGreenPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
}

void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::setYellow()
{
    mCurrentButtonPixmap = mButtonYellowPixmap;
    update();
}

void ImageButton::setGreen()
{
    mCurrentButtonPixmap = mButtonGreenPixmap;
    update();
}

void ImageButton::setRed()
{
    mCurrentButtonPixmap = mButtonRedPixmap;
    update();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    window->setFixedSize(220, 250);

    QSlider slider(Qt::Horizontal);
    slider.setParent(window);
    slider.setMinimum(0);
    slider.setMaximum(100);

    ImageButton circle(window);

    auto *layout = new QVBoxLayout(window);
    layout->addWidget(&circle);
    layout->addWidget(&slider);

    QObject::connect(&slider, &QSlider::valueChanged, [&slider, &circle](int newValue)
    {
        if(newValue>=0&&newValue<=33)
            circle.setGreen();
        else if(newValue>=34&&newValue<=63)
            circle.setYellow();
        else if(newValue>=64&&newValue<=100)
            circle.setRed();
    });

    slider.show();
    circle.show();
    window->show();

    app.exec();
}

#include <main.moc>