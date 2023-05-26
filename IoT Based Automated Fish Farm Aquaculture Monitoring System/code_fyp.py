import pandas as pd
import numpy as np
from prophet import Prophet
# from prophet.plot import plot_plotly, plot_components_plotly
import psycopg2
import psycopg2.extras







####################################################################################


conn = None
cur = None
  
try:
  conn = psycopg2.connect(
    host = 'localhost',
    database = 'postgres',
    user = 'postgres',
    password = '151214')
  cur = conn.cursor(cursor_factory=psycopg2.extras.DictCursor)

except Exception as error:

  print(error)


################################################################################ 

def read_data():


    #read_from_database


  
  
  cur.execute('select * from data10 order by date_time desc limit 2500')
  rows = cur.fetchall()
  

  df = pd.DataFrame(rows)
  df.columns = ['date_time','tds','ph','turbidity','ammonia','temperature']
    
  
  df['date_time'] = pd.to_datetime(df['date_time'])
  df.reset_index(drop=True, inplace=True)

  



  

  
  
  return df

df = read_data()




params = ['temperature','turbidity','ph','ammonia','tds']


def process(df,params):  
  

    for param in params:

        if param == "temperature":
            

            

                    
            # ds--> created_at, y-->Temperature

            df_t = df[['date_time','temperature']]
            df_t.columns = ['ds', 'y']

            m = Prophet(changepoint_prior_scale=0.0005)
            m.fit(df_t)
            future = m.make_future_dataframe(periods = 40, freq= 'H')
            forecast = m.predict(future)
            m.plot(forecast)
            Temp = forecast
        

        elif param == "turbidity":

        
        

            df_tr = df[['date_time','turbidity']]
            df_tr.columns = ['ds', 'y']

            m = Prophet()
            m.fit(df_tr)
            future = m.make_future_dataframe(periods = 40, freq= 'H')
            forecast = m.predict(future)
            m.plot(forecast)
            Turb = forecast
        
        elif param == "ph":
            
            

                    
            # ds--> created_at, y-->Temperature

            df_p = df[['date_time','ph']]
            df_p.columns = ['ds', 'y']

            m = Prophet()
            m.fit(df_p)
            future = m.make_future_dataframe(periods = 40, freq= 'H')
            forecast = m.predict(future)
            m.plot(forecast)
            ph = forecast
        
        elif param == "ammonia":
            

                    
            # ds--> created_at, y-->Temperature

            df_a = df[['date_time','ammonia']]
            df_a.columns = ['ds', 'y']

            m = Prophet()
            m.fit(df_a)
            future = m.make_future_dataframe(periods = 40, freq= 'H')
            forecast = m.predict(future)
            m.plot(forecast)
            Amm = forecast



        elif param == "tds":
            

                    
            # ds--> created_at, y-->Temperature

            df_td = df[['date_time','tds']]
            df_td.columns = ['ds', 'y']

            m = Prophet()
            m.fit(df_td)
            future = m.make_future_dataframe(periods = 40, freq= 'H')
            forecast = m.predict(future)
            m.plot(forecast)
            tds = forecast
    
    
    return Temp[['ds','yhat']], Turb[['ds','yhat']], ph[['ds','yhat']], Amm[['ds','yhat']], tds[['ds','yhat']]

    
        
  


Temp, Turb, ph, Amm, tds= process(df,params)

print(Temp.shape)
print(df['temperature'].shape)





n = len(Temp) - len(df)
print(n)

for i in range(n):
  df = df.append({'date_time' : np.nan, 'temperature' : np.nan,'turbidity' : np.nan,'ph' : np.nan,'ammonia' : np.nan,'tds': np.nan },    
        ignore_index = True) 
  
    # df and forecast lengths are equal
  

print(df)
print(Temp.shape)
print(df['temperature'].shape)


Temp['y'] = df[['temperature']].iloc[:,0].tolist()
Turb['y'] = df[['turbidity']].iloc[:,0].tolist()
ph['y'] = df[['ph']].iloc[:,0].tolist()
Amm['y'] = df[['ammonia']].iloc[:,0].tolist()
tds['y'] = df[['tds']].iloc[:,0].tolist()














      


def write_data(Temp, Turb, ph, Amm, tds):
       
    insert_values1 = list(Temp.itertuples(index = False))
    insert_values2 = list(Turb.itertuples(index = False))
    insert_values3 = list(ph.itertuples(index = False))
    insert_values4 = list(Amm.itertuples(index = False))
    insert_values5 = list(tds.itertuples(index = False))

    
    
    
    
    
    
    cur.execute('DROP TABLE IF EXISTS temp')
    cur.execute(''' CREATE TABLE IF NOT EXISTS temp(
                  ds timestamp without time zone,
                  

                  Predictions numeric,
                  Data numeric


                  

                                                      )
            ''')
    
    for record in insert_values1:
       cur.execute("INSERT INTO temp(ds,Predictions, Data) VALUES(%s, %s,%s)", record)

    cur.execute('DROP TABLE IF EXISTS turb')
    cur.execute(''' CREATE TABLE IF NOT EXISTS turb(
                  ds timestamp without time zone,
                  

                  Predictions numeric,
                  Data numeric


                  

                                                      )
            ''')
    
    for record in insert_values2:
       cur.execute("INSERT INTO turb(ds,Predictions, Data) VALUES(%s, %s,%s)", record)



    cur.execute('DROP TABLE IF EXISTS ph')
    cur.execute(''' CREATE TABLE IF NOT EXISTS ph(
                  ds timestamp without time zone,
                  

                  Predictions numeric,
                  Data numeric


                  

                                                      )
            ''')
    
    for record in insert_values3:
       cur.execute("INSERT INTO ph(ds,Predictions, Data) VALUES(%s, %s,%s)", record)




    cur.execute('DROP TABLE IF EXISTS amm')
    cur.execute(''' CREATE TABLE IF NOT EXISTS amm(
                  ds timestamp without time zone,
                  

                  Predictions numeric,
                  Data numeric


                  

                                                      )
            ''')
    
    for record in insert_values4:
       cur.execute("INSERT INTO amm(ds,Predictions, Data) VALUES(%s, %s,%s)", record)


    cur.execute('DROP TABLE IF EXISTS tds')
    cur.execute(''' CREATE TABLE IF NOT EXISTS tds(
                  ds timestamp without time zone,
                  

                  Predictions numeric,
                  Data numeric


                  

                                                      )
            ''')
    
    for record in insert_values5:
       cur.execute("INSERT INTO tds(ds,Predictions, Data) VALUES(%s, %s,%s)", record)





    
       
   


    


      
    
  




       



    conn.commit()
    


write_data(Temp, Turb, ph, Amm, tds)

cur.close()
conn.close()

 












 








  