async def contests(ctx):
  for contests in db['all_contests']:
  	contests_list = discord.Embed(title="Contest",color=0x2ecc71)
  	contests_list.add_field(name="Platform",value=db[contests]['platform'])
  	contests_list.add_field(name="Contest Name",value=db[contests]['contest'])
  	contests_list.add_field(name="Link",value=db[contests]['link'])
  	contests_list.add_field(name="Date",value=( db[contests]['day'] + "/" + db[contests]['month'] ) )
  	contests_list.add_field(name="Time",value=( db[contests]['hour'] + ":" + db[contests]['minutes'] ) )
  	await ctx.channel.send(embed=contests_list)
  	  	

@tasks.loop(hours=1)
async def contest_loop():
	await bot.wait_until_ready()
	channel = bot.get_channel(896310809888714772)
	await channel.send('This loop is executed')
	current = datetime.datetime.now(tz=gettz('Asia/Kolkata'))
	cday = current.day
	cmonth = current.month
	chour = current.hour
	cminutes = current.minute
	for contests in db['all_contests']:
		if(cday==contests['day'] and cmonth==contests['month'] and (chour==(contests['hour']-1) or chour==contests['hour'] ) ):
			clist = discord.Embed(title="Upcoming Contest Alert",color=0x992d22)
			clist.add_field(name="Platform",value=db[contests]['platform'])
			clist.add_field(name="Contest Name",value=db[contests]['contest'])
			clist.add_field(name="Link",value=db[contests]['link'])
			clist.add_field(name="Date",value=( db[contests]['day'] + "/" + db[contests]['month'] ) )
			clist.add_field(name="Time",value=( db[contests]['hour'] + ":" + db[contests]['minutes'] ) )
			clist.set_image(url="https://media.giphy.com/media/Rhr6OQDIoUOtDCcxD2/giphy.gif")
			await ctx.channel.send(embed=clist)
		elif(cday==contests['day'] and cmonth==contests['month'] and chour==(contests['hour']+1)):
			del db[contests]
			db['all_contests'].remove(contests)






@bot.command()
async def commands(ctx):
  	helpl = discord.Embed(title="Commands",color=0x95a5a6)
  	helpl.add_field(name=" ",value=" ")
  	helpl.add_field(name="!contests",value="Prints the list of all Upcoming Contests")
  	helpl.add_field(name="!info",value="Prints your own Username")
  	helpl.add_field(name="!commands",value="Specifies all the commands")
  	helpl.add_field(name="!set {Platform Name} {Handle}",value="Not in functionality currently !!!!" )
  	helpl.add_field(name="!add {Platform} {Date} {Time} {Link} {Contest}",value="Administrator Command Only")
  	await ctx.channel.send(embed=helpl)


contest_loop.start()
keep_alive()

bot.run(my_secret)
