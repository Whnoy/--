#include "headers.h"
#define SQR(x) ((x)*(x))

double cyrcle(double x, double y) {
    return SQR(x) + SQR(y) - 1;
}

double flower(double x, double y) {
    return pow(SQR(x) + SQR(y), 2) - SQR(x) + SQR(y) - 2; 
}

Node *findPoints(double (*func)(double, double), double x0, double y0) {
    // Все объявления переменных в начале функции
    const double eps = 1e-12, step = 1e-6, grad_eps = 1e-8;
    int max_iter = 10000000, iter = 0;
    int min_steps = 0, inner_iter = 0, max_inner = 0;
    double nuff = 0.0, x_start = 0.0, y_start = 0.0;
    Node *head = NULL, *buff = NULL, *next = NULL;
    double fx = 0.0, fy = 0.0, tx = 0.0, ty = 0.0, norm = 0.0;
    double x_mid = 0.0, y_mid = 0.0, fx_mid = 0.0, fy_mid = 0.0, tx_mid = 0.0, ty_mid = 0.0, norm_mid = 0.0;
    double x_next = 0.0, y_next = 0.0, dx = 0.0, dy = 0.0, dist = 0.0, grad_norm = 0.0;
    double fx0 = 0.0, fy0 = 0.0, tx0 = 0.0, ty0 = 0.0, norm0 = 0.0;
    double fx_cur = 0.0, fy_cur = 0.0, tx_cur = 0.0, ty_cur = 0.0, norm_cur = 0.0, dot = 0.0;

    head = malloc(sizeof(Node));
    if (!head) exit(EXIT_FAILURE);
    head->x = x0; head->y = y0; head->next = NULL;

    // Коррекция начальной точки
    nuff = func(head->x, head->y);
    inner_iter = 0;
    max_inner = 500;
    while (fabs(nuff) > eps && inner_iter++ < max_inner) {
        fx = (func(head->x + grad_eps, head->y) - func(head->x - grad_eps, head->y)) / (2 * grad_eps);
        fy = (func(head->x, head->y + grad_eps) - func(head->x, head->y - grad_eps)) / (2 * grad_eps);
        grad_norm = fx*fx + fy*fy + 1e-12;
        head->x -= nuff * fx / grad_norm;
        head->y -= nuff * fy / grad_norm;
        nuff = func(head->x, head->y);
    }

    buff = head;
    x_start = head->x;
    y_start = head->y;
    min_steps = (int)(2 * M_PI * 1.0 / step) - 5;

    // Сохраняем касательную в стартовой точке
    fx0 = (func(x_start + grad_eps, y_start) - func(x_start - grad_eps, y_start)) / (2 * grad_eps);
    fy0 = (func(x_start, y_start + grad_eps) - func(x_start, y_start - grad_eps)) / (2 * grad_eps);
    tx0 = -fy0; ty0 = fx0;
    norm0 = sqrt(tx0 * tx0 + ty0 * ty0);
    tx0 /= norm0; ty0 /= norm0;

    do {
        fx = (func(buff->x + grad_eps, buff->y) - func(buff->x - grad_eps, buff->y)) / (2 * grad_eps);
        fy = (func(buff->x, buff->y + grad_eps) - func(buff->x, buff->y - grad_eps)) / (2 * grad_eps);

        tx = -fy; ty = fx;
        norm = sqrt(tx * tx + ty * ty);
        if (norm < 1e-12) break;
        tx /= norm; ty /= norm;

        x_mid = buff->x + 0.5 * step * tx;
        y_mid = buff->y + 0.5 * step * ty;

        fx_mid = (func(x_mid + grad_eps, y_mid) - func(x_mid - grad_eps, y_mid)) / (2 * grad_eps);
        fy_mid = (func(x_mid, y_mid + grad_eps) - func(x_mid, y_mid - grad_eps)) / (2 * grad_eps);
        tx_mid = -fy_mid; ty_mid = fx_mid;
        norm_mid = sqrt(tx_mid * tx_mid + ty_mid * ty_mid);
        if (norm_mid < 1e-12) break;
        tx_mid /= norm_mid; ty_mid /= norm_mid;

        x_next = buff->x + step * tx_mid;
        y_next = buff->y + step * ty_mid;

        nuff = func(x_next, y_next);
        inner_iter = 0;
        max_inner = 50;
        while (fabs(nuff) > eps && inner_iter++ < max_inner) {
            fx = (func(x_next + grad_eps, y_next) - func(x_next - grad_eps, y_next)) / (2 * grad_eps);
            fy = (func(x_next, y_next + grad_eps) - func(x_next, y_next - grad_eps)) / (2 * grad_eps);
            grad_norm = fx*fx + fy*fy + 1e-12;
            x_next -= nuff * fx / grad_norm;
            y_next -= nuff * fy / grad_norm;
            nuff = func(x_next, y_next);
        }

        if (iter > min_steps) {
            dx = x_next - x_start;
            dy = y_next - y_start;
            dist = sqrt(dx*dx + dy*dy);

            // Касательная в текущей точке
            fx_cur = (func(x_next + grad_eps, y_next) - func(x_next - grad_eps, y_next)) / (2 * grad_eps);
            fy_cur = (func(x_next, y_next + grad_eps) - func(x_next, y_next - grad_eps)) / (2 * grad_eps);
            tx_cur = -fy_cur; ty_cur = fx_cur;
            norm_cur = sqrt(tx_cur * tx_cur + ty_cur * ty_cur);
            if (norm_cur > 1e-12) {
                tx_cur /= norm_cur; ty_cur /= norm_cur;
            }
            dot = tx_cur * tx0 + ty_cur * ty0;

            if (dist < step && dot > 0.99) // угол между касательными < ~8°
                break;
        }

        next = malloc(sizeof(Node));
        if (!next) exit(EXIT_FAILURE);
        next->x = x_next; next->y = y_next; next->next = NULL;
        buff->next = next;
        buff = next;
    } while (++iter < max_iter);

    // Явно замыкаем ломаную
    next = malloc(sizeof(Node));
    if (!next) exit(EXIT_FAILURE);
    next->x = x_start;
    next->y = y_start;
    next->next = NULL;
    buff->next = next;

    return head;
}

double findLength(Node *head) {
    double length = 0.0;
    Node *current = head;
    while (current->next != NULL) {
        length += sqrt(SQR(current->next->x - current->x) + SQR(current->next->y - current->y));
        current = current->next;
    }
    return length;
}

double findArea(Node *head) {
    double area = 0.0;
    Node *current = head;
    while (current->next != NULL) {
        area += (current->x * current->next->y - current->next->x * current->y);
        current = current->next;
    }
    return fabs(area) / 2.0;
}