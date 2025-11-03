#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void SetRandomGen(const std::mt19937& gen) {
        gen_ = gen;
    }

    [[nodiscard]] const std::mt19937& getGen() const {
        return gen_;
    }

private slots:
    void on_btn_edit_clicked();
    void on_btn_increment_clicked();
    void on_btn_find_clicked();
    void on_btn_count_clicked() const;
    void on_btn_pop_front_clicked();
    void on_btn_push_front_clicked();
    void on_btn_pop_back_clicked();
    void on_btn_push_back_clicked();
    void on_btn_erase_clicked();
    void on_btn_insert_clicked();
    void on_btn_clear_clicked();
    void on_btn_min_element_clicked();
    void on_btn_max_element_clicked();
    void on_btn_merge_sort_strict_clicked();
    void on_btn_merge_sort_unstrict_clicked();
    void on_btn_unique_clicked();
    void on_btn_reverse_clicked();
    void on_btn_shuffle_clicked();
    void on_btn_lower_bound_clicked();
    void on_btn_upper_bound_clicked();
    void on_btn_decrement_clicked();
    void on_btn_begin_clicked();
    void on_btn_end_clicked();
    void on_btn_template_tea_clicked();
    void on_btn_template_cake_clicked();
    void on_btn_resize_clicked();
    void on_list_widget_currentRowChanged(int currentRow);

private:
    void ApplyModel();
    void ApplyIterator();
    Ui::MainWindow *ui;
    Model dequeue_model_;
    std::random_device rd_;
    std::mt19937 gen_ = std::mt19937(rd_());
};
#endif // MAINWINDOW_H
