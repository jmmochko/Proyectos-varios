import requests
from datetime import date


def get_url(year):
    return f"https://nolaborables.com.ar/api/v2/feriados/{year}"


months = [
    'Enero',
    'Febrero',
    'Marzo',
    'Abril',
    'Mayo',
    'Junio',
    'Julio',
    'Agosto',
    'Septiembre',
    'Octubre',
    'Noviembre',
    'Diciembre']
days = [
    'Lunes',
    'Martes',
    'Miércoles',
    'Jueves',
    'Viernes',
    'Sábado',
    'Domingo']


def day_of_week(day, month, year):
    return days[date(year, month, day).weekday()]


class NextHoliday:
    def __init__(self):
        self.loading = True
        self.year = date.today().year
        self.holiday = None
        self.non_moveable = None
        self.moveable = None
        self.non_working = None
        self.long_weekend = None

    def set_next(self, holidays):
        now = date.today()
        today = {
            'day': now.day,
            'month': now.month
        }

        next_holidays = []
        next_holidays_nm = []
        next_holidays_m = []
        next_holidays_nw = []
        next_holidays_lw = []

        for h in holidays:
            if h['mes'] == today['month'] and h['dia'] > today['day'] or h['mes'] > today['month']:
                next_holidays.append(h)
                if h['tipo'] == 'inamovible':
                    next_holidays_nm.append(h)
                elif h['tipo'] == 'trasladable':
                    next_holidays_m.append(h)
                elif h['tipo'] == 'nolaborable':
                    next_holidays_nw.append(h)
                elif h['tipo'] == 'puente':
                    next_holidays_lw.append(h)

        default_nm = next_holidays_nm[0] if len(next_holidays_nm) > 0 else None
        default_m = next_holidays_m[0] if len(next_holidays_m) > 0 else None
        default_nw = next_holidays_nw[0] > 0 if len(next_holidays_nw) else None
        default_lw = next_holidays_lw[0] if len(next_holidays_lw) > 0 else None

        holiday = next(iter(next_holidays), holidays[0])
        non_moveable = next(iter(next_holidays_nm), default_nm)
        moveable = next(iter(next_holidays_m), default_m)
        non_working = next(iter(next_holidays_nw), default_nw)
        long_weekend = next(iter(next_holidays_lw), default_lw)

        self.loading = False
        self.holiday = holiday
        self.non_moveable = non_moveable
        self.moveable = moveable
        self.non_working = non_working
        self.long_weekend = long_weekend

    def fetch_holidays(self):
        response = requests.get(get_url(self.year))
        data = response.json()
        self.set_next(data)

    def info_holiday_render(self, holiday):
        if holiday is not None:
            print(holiday['motivo'])
            print("Fecha:")
            print(day_of_week(holiday['dia'], holiday['mes'], self.year))
            print(holiday['dia'])
            print(months[holiday['mes'] - 1])
        else:
            print("No hay proximo feriado")

    def render(self):
        if self.loading:
            print("Buscando...")
        else:
            print("Próximo feriado")
            self.info_holiday_render(self.holiday)
            print("Tipo:")
            print(self.holiday['tipo'])
            print("\nPróximo feriado inamovible")
            self.info_holiday_render(self.non_moveable)
            print("\nPróximo feriado trasladable")
            self.info_holiday_render(self.moveable)
            print("\nPróximo feriado no laborable")
            self.info_holiday_render(self.non_working)
            print("\nPróximo feriado puente")
            self.info_holiday_render(self.long_weekend)


next_holiday = NextHoliday()
next_holiday.fetch_holidays()
next_holiday.render()
