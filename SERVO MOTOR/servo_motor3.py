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
    Servo2 = MG90_96R_Class(Channel = 0, ZeroOffset = -10)
    Servo3 = MG90_96R_Class(Channel = 0, ZeroOffset = -10)


    try:
         while True:
            ch = input("input : ")
            # up
            # 상체
            if ch == 'r':
                Servo2.SetPos(160)
                Servo3.SetPos(160)
                time.sleep(1)

    except KeyboardInterrupt:
        print("Ctrl + C")

    except Exception as e:
        print(str(e))

    finally:
        print("exit profram")