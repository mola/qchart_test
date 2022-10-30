#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent)
   : QWidget(parent)
   , ui(new Ui::Test)
{
   ui->setupUi(this);
}

Test::~Test()
{
   delete ui;
}


void Test::on_toolButton_triggered(QAction *arg1)
{
}
