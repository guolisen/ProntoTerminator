#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <Qsci/qscilexercpp.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initializeUI();
    initializeEditor();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeUI()
{
    setWindowTitle("My Code Editor");
    setMenuBar(new QMenuBar(this));
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Open", this, SLOT(onOpen()), QKeySequence::Open);
    editor = new QsciScintilla(this);
    setCentralWidget(editor);
}

void MainWindow::onOpen()
{
    QString filename =  QFileDialog::getOpenFileName(this, tr("Open .cpp file"),
                                                     QDir::currentPath(),
                                                    "CPP (*.cpp *.h *.cxx)");
    if (filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return;
    editor->setText(file.readAll());
    file.close();
}

void MainWindow::initializeEditor()
{
    // codes based from http://eli.thegreenplace.net/2011/04/01/sample-using-qscintilla-with-pyqt/
    initializeFont();
    initializeMargin();
    initializeCaretLine();
    initializeLexer();
    // code based on QSciTE https://code.google.com/p/qscite/
    initializeFolding();
}

void MainWindow::initializeFont()
{
    QFont font("Courier", 12);
    font.setFixedPitch(true);
    editor->setFont(font);
}

void MainWindow::initializeMargin()
{
    QFontMetrics fontmetrics = QFontMetrics(editor->font());
    editor->setMarginsFont(editor->font());
    editor->setMarginWidth(0, fontmetrics.width(QString::number(editor->lines())) + 6);
    editor->setMarginLineNumbers(0, true);
    editor->setMarginsBackgroundColor(QColor("#cccccc"));

    connect(editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
}

void MainWindow::onTextChanged()
{
    QFontMetrics fontmetrics = editor->fontMetrics();
    editor->setMarginWidth(0, fontmetrics.width(QString::number(editor->lines())) + 6);
}

void MainWindow::initializeLexer()
{
    QsciLexerCPP *lexer = new QsciLexerCPP();
    lexer->setDefaultFont(editor->font());
    lexer->setFoldComments(true);
    editor->setLexer(lexer);
}

void MainWindow::initializeCaretLine()
{
    // Current line visible with special background color
    editor->setCaretLineVisible(true);
    editor->setCaretLineBackgroundColor(QColor("#ffe4e4"));
}

void MainWindow::initializeFolding()
{
    QsciScintilla::FoldStyle state =
            static_cast<QsciScintilla::FoldStyle>((!editor->folding()) * 5);
    if (!state)
        editor->foldAll(false);
    editor->setFolding(state);
}
