#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(
        ui->list_widget,
        &QListWidget::currentRowChanged,
        this,
        &MainWindow::on_list_widget_currentRowChanged
    );

    ApplyModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * <a href="https://youtu.be/6GCsQRS3kM?si=StDcSnZ6TT7Tpvlm">Redecorate - Twenty One Pilots</a>
 *
 *  <strong> Table of content </strong>
 * <li>\ref model_and_iterator "Applying Model and Iterator"</li>
 * <li>\ref element_actions "Element actions"</li>
 * <li>\ref methods "Methods"</li>
 * <li>\ref algorithms "Algorithms"</li>
 * <li>\ref iterators "Iterators"</li>
 * <li>\ref templates "Templates"</li>
 * <li>\ref resize "Resize"</li>
 * <li>\ref list_widget "List Widget"</li>
 */


/**
 * <a id="model-and-iterator"></a>
 * <h2>Applying Model and Iterator</h2>
 */

void MainWindow::ApplyModel() {
    const auto it_saved = dequeue_model_.it;
    ui->list_widget->blockSignals(true);
    ui->list_widget->clear();

    for (int i = 0; i < dequeue_model_.items.size(); ++i) {
        ui->list_widget->addItem(
            QString::number(i)
            + QString(": ")
            + QString::fromStdString(dequeue_model_.items[i])
        );
    }

    ui->list_widget->addItem(QString("end"));
    ui->list_widget->blockSignals(false);
    dequeue_model_.it = it_saved;

    dequeue_model_.items.empty()
            ? ui->btn_pop_back->setEnabled(false)
            : ui->btn_pop_back->setEnabled(true);
    dequeue_model_.items.empty()
            ? ui->btn_pop_front->setEnabled(false)
            : ui->btn_pop_front->setEnabled(true);

    ui->txt_size->setText(QString::number(dequeue_model_.items.size()));

    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    const auto it_offset = dequeue_model_.it - dequeue_model_.items.begin();
    const bool is_end = dequeue_model_.items.end() == dequeue_model_.it;
    const bool is_first = dequeue_model_.items.begin() == dequeue_model_.it;

    ui->txt_elem_content->setText(is_end ? "" : QString::fromStdString(*dequeue_model_.it));
    ui->list_widget->setCurrentRow(static_cast<int>(it_offset));
    ui->btn_edit->setDisabled(is_end);
    ui->btn_erase->setDisabled(is_end);
    ui->btn_increment->setDisabled(is_end);
    ui->btn_decrement->setDisabled(is_first);
}


/**
 * <a id="element-actions"></a>
 * <h2>Element actions</h2>
 */
void MainWindow::on_btn_edit_clicked() {
    if (dequeue_model_.it != dequeue_model_.items.end()) {
        const QString str = ui->txt_elem_content->text();
        if (!str.isEmpty()) {
            *dequeue_model_.it = str.toStdString();
            ApplyModel();
        }
    }
}


void MainWindow::on_btn_find_clicked() {
    const std::string text = ui->txt_elem_content->text().toStdString();
    dequeue_model_.it = std::find(
        dequeue_model_.items.begin(),
        dequeue_model_.items.end(),
        text);
    ApplyIterator();
}


void MainWindow::on_btn_count_clicked() const {
    const std::string text = ui->le_count->text().toStdString();
    int amount = 0;
    for (const auto& elem : dequeue_model_.items) {
        if (elem == text)
            amount++;
    }
    ui->lbl_count->setText(QString::number(amount));
}


/**
 * <a id="methods"></a>
 * <h2>Methods</h2>
 *
 */
void MainWindow::on_btn_pop_front_clicked() {
    if (!dequeue_model_.items.empty()) {
        dequeue_model_.items.pop_front();
        dequeue_model_.it = dequeue_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_push_front_clicked() {
    const std::string txt = ui->txt_elem_content->text().toStdString();
    if (txt.empty())
        return; // Каширская Елизавета Натановна так писала :D

    dequeue_model_.items.push_front(txt);
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_pop_back_clicked() {
    if (!dequeue_model_.items.empty()) {
        dequeue_model_.items.pop_back();
        dequeue_model_.it = dequeue_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_push_back_clicked() {
    const std::string txt = ui->txt_elem_content->text().toStdString();
    if (txt.empty())
        return;

    dequeue_model_.items.push_back(txt);
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_erase_clicked() {
    if (dequeue_model_.it == dequeue_model_.items.end())
        return; // Каширская Елизавета Натановна так писала :D

    dequeue_model_.items.erase(dequeue_model_.it);
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_insert_clicked() {
    if (const QString text = ui->txt_elem_content->text(); !text.isEmpty()) {
        dequeue_model_.items.insert(dequeue_model_.it, text.toStdString());
        dequeue_model_.it = dequeue_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_clear_clicked() {
    dequeue_model_.items.clear();
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


/**
 * <a id="algorithms"></a>
 * <h2>Algorithms</h2>
 *
 */
void MainWindow::on_btn_min_element_clicked() {
    dequeue_model_.it = std::min_element(dequeue_model_.items.begin(), dequeue_model_.items.end());
    ApplyIterator();
}


void MainWindow::on_btn_max_element_clicked() {
    dequeue_model_.it = std::max_element(dequeue_model_.items.begin(), dequeue_model_.items.end());
    ApplyIterator();
}


void MainWindow::on_btn_merge_sort_strict_clicked() {
    const std::deque<std::string> data = dequeue_model_.items;
    dequeue_model_.items = MergeSort<std::string>(data, std::less<std::string>{});
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_merge_sort_unstrict_clicked() {
    dequeue_model_.items = MergeSort(dequeue_model_.items, [](
        const std::string& a, const std::string& b
        ) {
        return QString::fromStdString(a).compare(
            QString::fromStdString(b),
            Qt::CaseInsensitive
        ) < 0;
    });
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_unique_clicked() {
    if (!std::is_sorted(dequeue_model_.items.begin(), dequeue_model_.items.end()))
        return;

    const auto new_end = std::unique(dequeue_model_.items.begin(), dequeue_model_.items.end());
    dequeue_model_.items.erase(new_end, dequeue_model_.items.end());
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_reverse_clicked() {
    std::reverse(dequeue_model_.items.begin(), dequeue_model_.items.end());
    ApplyModel();
}


void MainWindow::on_btn_shuffle_clicked() {
    std::shuffle(dequeue_model_.items.begin(), dequeue_model_.items.end(), gen_);
    ApplyModel();
}


void MainWindow::on_btn_lower_bound_clicked() {
    if (!std::is_sorted(dequeue_model_.items.begin(), dequeue_model_.items.end()))
        return;

    dequeue_model_.it = std::lower_bound(
        dequeue_model_.items.begin(),
        dequeue_model_.items.end(),
        ui->txt_elem_content->text().toStdString()
    );
    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked() {
    if (!std::is_sorted(dequeue_model_.items.begin(), dequeue_model_.items.end()))
        return;

    dequeue_model_.it = std::upper_bound(
        dequeue_model_.items.begin(),
        dequeue_model_.items.end(),
        ui->txt_elem_content->text().toStdString()
    );
    ApplyIterator();
}


/**
 * <a id="iterators"></a>
 * <h2>Iterators</h2>
 *
 */
void MainWindow::on_btn_decrement_clicked() {
    --dequeue_model_.it;
    ApplyIterator();
}


void MainWindow::on_btn_increment_clicked() {
    ++dequeue_model_.it;
    ApplyIterator();
}


void MainWindow::on_btn_begin_clicked() {
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked() {
    dequeue_model_.it = dequeue_model_.items.end();
    ApplyIterator();
}



/**
 * <a id="templates"></a>
 * <h2>Templates</h2>
 *
 */
void MainWindow::on_btn_template_tea_clicked() {
    dequeue_model_.items = tea;
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_template_cake_clicked() {
    dequeue_model_.items = cakes;
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


/**
 * <a id="resize"></a>
 * <h2>Resize</h2>
 *
 */
void MainWindow::on_btn_resize_clicked() {
    // Met once, so i decide to keep em only in function
    constexpr int MIN_SIZE = 0;
    constexpr int MAX_SIZE = 1000;

    int size = ui->txt_size->text().toInt();
    size = std::max(MIN_SIZE, std::min(MAX_SIZE, size));
    ui->txt_size->setText(QString::number(size));

    dequeue_model_.items.resize(static_cast<std::deque<std::string>::size_type>(size));
    dequeue_model_.it = dequeue_model_.items.begin();
    ApplyModel();
}


/**
 * <a id="list-widget"></a>
 * <h2>List Widget</h2>
 */
void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow == static_cast<int>(dequeue_model_.items.size())) {
        dequeue_model_.it = dequeue_model_.items.end();
    } else {
        dequeue_model_.it = dequeue_model_.items.begin();
        std::advance(dequeue_model_.it, currentRow);
    }
    ApplyIterator();
}
