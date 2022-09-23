import Adafruit_PCA9685
import time

class MG90_96R_Class:
    def __init__(self, Channel, ZeroOffset):
        self.servo_num = Channel
        self.servo_offset = ZeroOffset

        # 원하는 주소 및/또는 버스를 사용하여 PCA9685를 초기화합니다.
        self.Pwm = Adafruit_PCA9685.PCA9685(address = 0x40, busnum = 1)

        # 주파수를 60[Hz]로 설정
        self.Pwm.set_pwm_freq(60)

    # 최소 및 최대 서보 펄스 길이 구성
    def SetPos(self, pos):
        pulse = (650 - 150) * pos / 180 + 150 + self.servo_offset
        self.Pwm.set_pwm(self.servo_num, 0, int(pulse))

    # 서보모터 초기화
    def Cleanup(self):
        self.SetPos(90)
        time.sleep(1)

if __name__ == '__main__':
    # PCA9685모듈 에서 사용할 채널 설정
    Servo0 = MG90_96R_Class(Channel = 0, ZeroOffset = -10)
    Servo1 = MG90_96R_Class(Channel = 1, ZeroOffset = -10)
    Servo2 = MG90_96R_Class(Channel = 2, ZeroOffset = -10)
    Servo3 = MG90_96R_Class(Channel = 3, ZeroOffset = -10)
    Servo4 = MG90_96R_Class(Channel = 4, ZeroOffset = -10)
    Servo5 = MG90_96R_Class(Channel = 5, ZeroOffset = -10)
    Servo6 = MG90_96R_Class(Channel = 6, ZeroOffset = -10)
    Servo7 = MG90_96R_Class(Channel = 7, ZeroOffset = -10)
    Servo8 = MG90_96R_Class(Channel = 8, ZeroOffset = -10)
    Servo9 = MG90_96R_Class(Channel = 9, ZeroOffset = -10)
    Servo10 = MG90_96R_Class(Channel = 10, ZeroOffset = -10)


    try:
         while True:
            ch = input("input : ")
            # up
            # 상체
            if ch == 'q':
                Servo0.SetPos(20)
                time.sleep(1)

            if ch == 'w':
                Servo1.SetPos(170)
                time.sleep(1)
            # 다리
            if ch == 'r':
                Servo2.SetPos(150)
                Servo3.SetPos(150)
                time.sleep(1)

            # 등받이
            if ch == 't':
                Servo4.SetPos(70)
                Servo5.SetPos(110)
                Servo6.SetPos(70)
                time.sleep(1)

            # 범퍼
            if ch == 'u':
                Servo7.SetPos(60)
                Servo8.SetPos(60)
                Servo9.SetPos(60)
                Servo10.SetPos(60)
                time.sleep(1)

            # down
            #상체
            if ch == 'a':
                Servo0.SetPos(150)
                time.sleep(1)

            if ch == 's':
                Servo1.SetPos(90)
                time.sleep(1)

            # 다리
            if ch == 'f':
                Servo2.SetPos(40)
                Servo3.SetPos(40)
                time.sleep(1)

            # 등받이
            if ch == 'g':
                Servo4.SetPos(0)
                Servo5.SetPos(180)
                Servo6.SetPos(35)
                time.sleep(1)

            # 범퍼
            if ch == 'j':
                Servo7.SetPos(0)
                Servo8.SetPos(0)
                Servo9.SetPos(0)
                Servo10.SetPos(0)
                time.sleep(1)

    except KeyboardInterrupt:
        print("Ctrl + C")

    except Exception as e:
        print(str(e))

    finally:
        print("exit profram")
        