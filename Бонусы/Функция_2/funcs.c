#include "headers.h"


void freePoints(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

double func(double x, double y) {
    return x + pow(x,3)*y + x*x + x*y*y + pow(x,4)*y + 0.3;
}


// Поиск всех корней по y для каждого x
Node *findPoints(double (*func)(double, double), double xmin, double xmax, double ymin, double ymax) {
    double DX = 1e-3, DY = 1e-3, EPS = 1e-8;
    Node *head = NULL, *tail = NULL;
    double x, y1, y2, f1, f2, left, right, mid, fmid, y_root;
    Node *node;
    for (x = xmin; x <= xmax; x += DX) {
        for (y1 = ymin; y1 < ymax; y1 += DY) {
            y2 = y1 + DY;
            f1 = func(x, y1);
            f2 = func(x, y2);
            if (f1 * f2 > 0) continue; // нет смены знака — нет корня
            // Бисекция на [y1, y2]
            left = y1;
            right = y2;
            while (right - left > EPS) {
                mid = 0.5 * (left + right);
                fmid = func(x, mid);
                if (f1 * fmid <= 0) {
                    right = mid;
                    f2 = fmid;
                } else {
                    left = mid;
                    f1 = fmid;
                }
            }
            y_root = 0.5 * (left + right);
            // Добавляем найденную точку
            node = malloc(sizeof(Node));
            node->x = x;
            node->y = y_root;
            node->next = NULL;
            if (!head) head = node;
            else tail->next = node;
            tail = node;
        }
    }
    return head;
}


void insertRectanglePoints(Node **head, double xmin, double xmax, double ymin, double ymax, double step, double threshold) {
    Node *node;
    for (double x = xmin; x <= xmax; x += step) {
        for (double y = ymin; y <= ymax; y += step) {
            if (fabs(func(x, y)) < threshold) {
                node = malloc(sizeof(Node));
                node->x = x;
                node->y = y;
                node->next = *head;
                *head = node;
            }
        }
    }
}


double findLength(Node *head) {
    double length = 0.0;
    Node *cur = head;
    while (cur && cur->next) {
        double dx = cur->next->x - cur->x;
        double dy = cur->next->y - cur->y;
        length += sqrt(dx * dx + dy * dy);
        cur = cur->next;
    }
    return length;
}


double findArea(Node *head) {
    double area = 0.0;
    Node *cur = head;
    while (cur && cur->next) {
        area += (cur->x * cur->next->y - cur->next->x * cur->y);
        cur = cur->next;
    }
    return fabs(area) / 2.0;
}

