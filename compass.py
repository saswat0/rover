from i2clibraries import i2c_hmc5883l

class Compass():
	def __init__(self):
		self.connectCompass()
		self.value=0
	
	def connectCompass(self):
		try:
			self.hm = i2c_hmc5883l.i2c_hmc5883l(1) #i2c channel 1
			self.hm.setContinuousMode()
		except Exception as e:
			raise e
	
	def getCompassAngle(self):
		try:
				self.hm.setDeclination(-1,6) #Declination of our place
				self.value = hm.heading
				return self.value
		except TypeError as e:
			raise e
